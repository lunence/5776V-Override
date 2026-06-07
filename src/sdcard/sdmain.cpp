#include "sdmain.hpp"

class sdWriter {
    private:
        // Structure with file settings
        // Each file has its own settings so it doesn't conflict
        struct fileData {
            bool isWriting;
            int frequency;
        };

        // Map of file names to file settings, each filename is assigned to a fileData instance
        std::unordered_map<std::string, fileData> files;

    public:
        // Start logging data to a given file
        void startWrite(const std::string& filename) {
            // set isWriting to true, so that writeData will write
            files[filename].isWriting = true;
        }

        // Stop logging data to a given file
        void stopWrite(const std::string& filename) {
            // set isWriting to false, so that writeData will not write
            files[filename].isWriting = false;
        }

        // Change the logging frequency for a given file
        void changeFrequency(const std::string& filename, int newFrequency) {
            // set frequency to a new frequency, default 10ms
            files[filename].frequency = newFrequency;
        }

        // Write data to a given file
        void writeData(const std::string& filename) {
            // open file in append mode
            std::string path = "/usd/" + filename;
            FILE* usd_file_write = fopen(path.c_str(), "a");

            // invalid file handling
            if (usd_file_write == nullptr) {
                printf("Failed to open file.\n");
                return;
            }

            // while isWriting is true (based off the toggle)
            while (files[filename].isWriting) {
                // fetch pose data
                auto pose = chassis.getPose();

                // write pose data
                fprintf(
                    usd_file_write,
                    "%f,%f,%f\n",
                    pose.x,
                    pose.y,
                    pose.theta
                );

                // ensure changes are made
                fflush(usd_file_write);

                // delay for frequency in ms
                pros::delay(files[filename].frequency);
            }

            // close and save file
            fclose(usd_file_write);
        }
};