#pragma once

#include "lemlib/api.hpp"
#include "objects.hpp"
#include <cstdio>
#include <string>
#include <unordered_map>

class sdWriter {
    private:
        // Structure with file settings
        // Each file has its own settings so it doesn't conflict
        struct fileData {
            bool isWriting = false;
            int frequency = 10; // default 10ms
        };

        // Map of file names to file settings, each filename is assigned to a fileData instance
        std::unordered_map<std::string, fileData> files;

    public:
        // Start logging data to a given file
        void startWrite(const std::string& filename);

        // Stop logging data to a given file
        void stopWrite(const std::string& filename);

        // Change the logging frequency for a given file
        void changeFrequency(const std::string& filename, int newFrequency);

        // Write data to a given file
        void writeData(const std::string& filename);
};