#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H

#include "observer.h"
#include <fstream>
#include <string>

class LogObserver : public Observer {
private:
    std::ofstream file;

public:
    explicit LogObserver(const std::string& filename) {
        file.open(filename, std::ios::app);
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open log file: " + filename);
        }
    }

    ~LogObserver() {
        if (file.is_open()) {
            file.flush();
            file.close();
        }
    }

    void update(const std::string& message) override {
        if (file.is_open()) {
            file << message << std::endl;
        }
    }
};

#endif

