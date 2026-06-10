#include "sdcard/sdmain.hpp"

// Map of file names to file settings, each filename is assigned to a fileData instance
std::unordered_map<std::string, sdWriter::fileData> sdWriter::files;

std::string sdWriter::activeFile = "";
pros::Mutex sdWriter::filesMutex;

void sdWriter::initFile(const std::string& filename) {
    std::string path = "/usd/" + filename;
    FILE* usd_file_write = fopen(path.c_str(), "r");

    if (usd_file_write == nullptr) {
        usd_file_write = fopen(path.c_str(), "w");
        if (usd_file_write == nullptr) {
            printf("Failed to create file.\n");
            return;
        }

        fclose(usd_file_write);

        files[filename] = fileData{};
    } else {
        fclose(usd_file_write);
        if (files.find(filename) == files.end()) {
            files[filename] = fileData{};
        }
    }
}

// Start logging data to a given file
void sdWriter::setData(const std::string& filename, const std::vector<std::function<std::string()>>& values) {
    files[filename].values = values;
}

// Start logging data to a given file
void sdWriter::startWrite(const std::string& filename) {
    // set isWriting to true, so that writeData will write
    files[filename].isWriting = true;
}

// Stop logging data to a given file
void sdWriter::stopWrite(const std::string& filename) {
    // set isWriting to false, so that writeData will not write
    files[filename].isWriting = false;
}

// Change the logging frequency for a given file
void sdWriter::changeFrequency(const std::string& filename, int newFrequency) {
    // set frequency to a new frequency, default 10ms
    files[filename].frequency = newFrequency;
}

// Write data to a given file
void sdWriter::writeData(const std::string& filename) {
    // open file in append mode
    std::string path = "/usd/" + filename;
    FILE* usd_file_write = fopen(path.c_str(), "a");

    // invalid file handling
    if (usd_file_write == nullptr) {
        initFile(filename);
        usd_file_write = fopen(path.c_str(), "a");
        if (usd_file_write == nullptr) {
            printf("Failed to open file for appending.\n");
            return;
        }
    }

    // while isWriting is true (based off the toggle)
    while (files[filename].isWriting) {
        bool first = true;

        for (auto& getter : files[filename].values) {
            if (!first)
                fprintf(usd_file_write, ",");

            fprintf(usd_file_write, "%s", getter().c_str());

            first = false;
        }

        fprintf(usd_file_write, "\n");
        fflush(usd_file_write);

        pros::delay(files[filename].frequency);
    }

    // close and save file
    fclose(usd_file_write);
}

// i suppose this is runWriter
void sdWriter::runWriter() {
    // iterate through all files in the map
    for (const auto& pair : files) {
        // extract filename and data for each file
        const std::string& filename = pair.first;
        const fileData& data = pair.second;

        // for each file, if it's writing, then write data to the filename
        if (data.isWriting) {
            sdWriter::writeData(filename);
        }
    }
}   


void sdWriter::logRow(const std::string& filename, const std::vector<std::string>& fields) {
    if (filename.empty()) return;  // logging not set up: silently do nothing

    std::string path = "/usd/" + filename;
    FILE* usd_file_write = fopen(path.c_str(), "a");
    if (usd_file_write == nullptr) return;

    bool first = true;
    for (const std::string& field : fields) {
        if (!first) fprintf(usd_file_write, ",");
        fprintf(usd_file_write, "%s", field.c_str());
        first = false;
    }
    fprintf(usd_file_write, "\n");
    fclose(usd_file_write);
}

// Tagged marker row, e.g. LABEL,184223,moveToPoint start
void sdWriter::writeLabel(const std::string& filename, const std::string& label) {
    logRow(filename, {"LABEL", std::to_string(pros::millis()), label});
}
