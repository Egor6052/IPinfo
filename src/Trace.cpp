#include "../lib/Trace.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <memory>
#include <array>

Trace::Trace() {
    this->IP = "-";
    this->URL = "-";
    this->index = 1;
}

Trace::~Trace() { }

void Trace::getURL() {
    std::string valueURL;
    std::cout << "Enter URL:" << std::endl;
    std::cin >> valueURL;
    setURL(valueURL);
}

void Trace::setURL(std::string& valueURL) {
    this->URL = valueURL;
}

int Trace::getIndex() {
    return index;
}

void Trace::Print() {
    std::cout << "Your URL: " << URL << std::endl;
    std::cout << "IP" << index << ": " << IP << std::endl;
}


void Trace::executeTracerouteScript() {
    const std::string scriptPath = "./bash/traceroute.sh";
    
    std::string command = "bash " + scriptPath + " " + this->URL;

    std::array<char, 128> buffer;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        std::cerr << "Failed to execute script!" << std::endl;
        return;
    }

    std::vector<std::string> ipAddresses;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::string line = buffer.data();

        if (!line.empty() && line.find("IP:") == std::string::npos) {
            ipAddresses.push_back(line);
        }
    }

    for (size_t i = 0; i < ipAddresses.size(); ++i) {
        std::cout << "IP" << i + 1 << ": " << ipAddresses[i] << std::endl;
        executeIPinfo(ipAddresses[i]);
    }
}


void Trace::executeIPinfo(const std::string& ipAddress) {
    const std::string scriptPath = "./bash/IPinfo.sh";

    std::string command = "bash " + scriptPath + " " + ipAddress;

    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

    if (!pipe) {
        std::cerr << "Failed to execute IPinfo script!" << std::endl;
        return;
    }

    // Читаємо результат виконання скрипта
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    std::cout << "IP Info for " << ipAddress << ":\n" << result << std::endl;
}

