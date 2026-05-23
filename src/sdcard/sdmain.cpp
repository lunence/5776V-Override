#include "lemlib/api.hpp"
#include "objects.hpp"
#include "sdmain.hpp"

#include <cstdio>
#include <string>

class sdWriter {
    private:
        bool isWriting = false;
        int frequency = 10;

    public:
        void startWrite() {
            // set isWriting to true, so that writeData will write
            isWriting = true;
        }
        void stopWrite() {
            // set isWriting to false, so that writeData will not write
            isWriting = false;
        }
        void changeFrequency(int newFrequency) {
            // set frequency to a new frequency, default 10ms
            frequency = newFrequency;
        }
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
            while (isWriting) {
                // fetch pose data
                currPoseX = drivetrain.getPose().x;
                currPoseY = drivetrain.getPose().y;
                currPoseTheta = drivetrain.getPose().theta * 180.0 / M_PI;

                // write pose data
                fprintf(
                    usd_file_write,
                    "%f,%f,%f\n",
                    currPoseX,
                    currPoseY,
                    currPoseTheta
                );

                // ensure changes are made
                fflush(usd_file_write);

                // delay for frequency in ms
                pros::delay(frequency);
            }

            // close and save file
            fclose(usd_file_write);
        }
};