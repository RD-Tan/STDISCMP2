#include "ConfigReader.h"

void parseValue(std::string key, std::string strValue, int* configPointer) {
    try {
        size_t idx = 0;
        int parsedValue = std::stoi(strValue, &idx);
        
        if (idx != strValue.length()) {
            std::cerr << "Value given for " << key << " not valid base 10 number.\n";
            exit(1);
        }

        //if (parsedValue < 1) {
        //    std::cerr << key << "  given is zero or negative. Must be positive.\n";
        //    exit(1);
        //}

        *configPointer = parsedValue;
    }
    catch (const std::out_of_range&) {
        std::cerr << "Value given for " << key << " exceeds int.\n";
        exit(1);
    }
    catch (const std::invalid_argument&) {
        std::cerr << "Value given for " << key << " not valid base 10 number.\n";
        exit(1);
    }
}

Config readConfig(const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open config.";
        exit(1);
    }

    std::string line;
    Config config = {};
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        if (key == "n") {
            parseValue(key, value, &config.numConsumers);
        }
        else if (key == "t") {
            parseValue(key, value, &config.tankCount);
        }
        else if (key == "h") {
            parseValue(key, value, &config.healerCount);
        }
        else if (key == "d") {
            parseValue(key, value, &config.DPSCount);
        }
        else if (key == "t1") {
            parseValue(key, value, &config.minWaitTime);
        }
        else if (key == "t2") {
            parseValue(key, value, &config.maxWaitTime);
        }
    }
    return config;
}