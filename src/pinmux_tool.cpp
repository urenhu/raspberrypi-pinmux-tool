#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>

struct PinRole {
    std::string role;
    int gpio;
    int physical;
    std::string alt;
};

using AltMap = std::unordered_map<std::string, std::vector<PinRole>>;
using PeripheralMap = std::unordered_map<std::string, AltMap>;

PeripheralMap pinmuxDB = {
    { "uart4", {
        { "ALT0", {
            { "TXD4", 8, 24, "ALT0" },
            { "RXD4", 9, 21, "ALT0" },
            { "CTS4", 10, 19, "ALT0" },
            { "RTS4", 11, 23, "ALT0" }
        }},
        { "ALT3", {
            { "TXD4", 32, 12, "ALT3" },
            { "RXD4", 33, 13, "ALT3" },
            { "CTS4", 34, 35, "ALT3" },
            { "RTS4", 35, 38, "ALT3" }
        }}
    }},
    { "uart5", {
        { "ALT3", {
            { "TXD5", 12, 32, "ALT3" },
            { "RXD5", 13, 33, "ALT3" },
            { "CTS5", 14, 8, "ALT3" },
            { "RTS5", 15, 10, "ALT3" }
        }}
    }},
    { "i2c0", {
        { "ALT0", {
            { "SDA0", 0, 27, "ALT0" },
            { "SCL0", 1, 28, "ALT0" }
        }}
    }},
    { "i2c1", {
        { "ALT0", {
            { "SDA1", 2, 3, "ALT0" },
            { "SCL1", 3, 5, "ALT0" }
        }}
    }},
    { "spi0", {
        { "ALT0", {
            { "MOSI", 10, 19, "ALT0" },
            { "MISO", 9, 21, "ALT0" },
            { "SCLK", 11, 23, "ALT0" },
            { "CE0", 8, 24, "ALT0" },
            { "CE1", 7, 26, "ALT0" }
        }}
    }},
    { "spi1", {
        { "ALT4", {
            { "MOSI", 20, 38, "ALT4" },
            { "MISO", 19, 35, "ALT4" },
            { "SCLK", 21, 40, "ALT4" },
            { "CE0", 18, 12, "ALT4" },
            { "CE1", 17, 11, "ALT4" }
        }}
    }}
};

void listPeripheralOptions(const std::string& peripheral) {
    auto it = pinmuxDB.find(peripheral);
    if (it == pinmuxDB.end()) {
        std::cerr << "❌ Unknown peripheral: " << peripheral << "\n";
        return;
    }

    std::cout << "🔧 Available mappings for " << peripheral << ":\n";
    for (const auto& [alt, pins] : it->second) {
        std::cout << "  " << alt << ":\n";
        for (const auto& role : pins) {
            std::cout << "    " << role.role << ": GPIO" << role.gpio
                      << " (Pin " << role.physical << "), " << role.alt << "\n";
        }
    }
}

void promptPeripheralSelection(const std::string& peripheral) {
    auto it = pinmuxDB.find(peripheral);
    if (it == pinmuxDB.end()) return;

    std::string altChoice;
    std::cout << "\nSelect ALT function (";
    for (const auto& [alt, _] : it->second) std::cout << alt << " ";
    std::cout << "): ";
    std::getline(std::cin, altChoice);

    auto altIt = it->second.find(altChoice);
    if (altIt == it->second.end()) {
        std::cerr << "❌ Invalid ALT selection.\n";
        return;
    }

    std::cout << "✅ Selected pins:\n";
    for (const auto& role : altIt->second) {
        std::cout << "  " << role.role << ": GPIO" << role.gpio
                  << " (Pin " << role.physical << ")\n";
    }

    std::cout << "\nApply overlay for " << peripheral << "? [Y/n]: ";
    std::string confirm;
    std::getline(std::cin, confirm);
    if (confirm.empty() || confirm == "Y" || confirm == "y") {
        std::string cmd = "sudo dtoverlay=" + peripheral;
        for (const auto& role : altIt->second) {
            cmd += "," + role.role + "_pin=" + std::to_string(role.gpio);
        }
        std::cout << "🚀 Running: " << cmd << "\n";
        std::system(cmd.c_str());
    } else {
        std::cout << "⚠️ Overlay not applied.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3 || std::string(argv[1]) != "-p") {
        std::cerr << "📌 Usage: " << argv[0] << " -p <peripheral>\n";
        std::cerr << "Supported peripherals: uart4, uart5, spi0, spi1, i2c0, i2c1\n";
        return 1;
    }

    std::string peripheral = argv[2];
    listPeripheralOptions(peripheral);
    promptPeripheralSelection(peripheral);

    return 0;
}
