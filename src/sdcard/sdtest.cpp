#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"
#include "pros/rtos.hpp"
#include <cmath>
#include <cstdio>
#include <string>

void sdTest::run() {
    const std::string file = sdWriter::getTimestamp() + "_" + "sdtest.csv";

    printf("[sdtest] start\n");

    // 1. initFile: create the file on the SD card
    sdWriter::initFile(file);
    sdWriter::activeFile = file;

    // 2. logRow: write a header row directly (synchronous, no streaming yet)
    sdWriter::logRow(file, {"time_ms", "counter", "sin", "cos", "fake_x", "fake_y"});

    // 3. writeLabel: drop a tagged marker
    sdWriter::writeLabel(file, "test start");

    // 4. setData: register synthetic getters. Each closure produces a fresh
    //    string every time the background runWriter task calls it.
    int counter = 0;
    sdWriter::setData(file, {
        // time (milliseconds)
        []() { return std::to_string(pros::millis()); },

        // counter
        [&counter]() { return std::to_string(counter++); },

        // sine
        []() {
            double t = pros::millis() / 1000.0;
            return std::to_string(std::sin(t));
        },

        // cosine
        []() {
            double t = pros::millis() / 1000.0;
            return std::to_string(std::cos(t));
        },

        // fake x
        []() {
            // fake x: linear ramp
            double t = pros::millis() / 1000.0;
            return std::to_string(12.0 * t);
        },

        // fake y
        []() {
            // fake y: parabola
            double t = pros::millis() / 1000.0;
            return std::to_string(0.5 * t * t);
        },
    });

    // 5. changeFrequency: 50 ms between rows (20 rows / sec)
    sdWriter::changeFrequency(file, 50);

    // 6. startWrite: flips the isWriting flag. NOTE: runWriter as written in
    //    sdmain.cpp only iterates `files` once at task startup, so it won't
    //    pick this up. We spawn writeData directly so we can actually verify
    //    the streaming write path works.
    sdWriter::startWrite(file);
    pros::Task writeTask([file]() { sdWriter::writeData(file); }, "sdtest write");

    // Let it stream for 2 seconds at 50 ms -> ~40 rows
    pros::delay(2000);

    // 7. writeLabel mid-stream so you can find this moment in the CSV later
    sdWriter::writeLabel(file, "frequency change to 10ms");

    // 8. changeFrequency mid-stream: speed up to 10 ms (100 rows / sec)
    sdWriter::changeFrequency(file, 10);

    // Stream for another 2 seconds at 10 ms -> ~200 rows
    pros::delay(2000);

    sdWriter::writeLabel(file, "stopping write");

    // 9. stopWrite: writeData loop exits, file gets closed
    sdWriter::stopWrite(file);

    // Give the background task a beat to actually close the file
    pros::delay(200);

    // 10. logRow after stop: proves logRow works independent of the streaming loop
    sdWriter::logRow(file, {"POST_STOP", std::to_string(pros::millis()), "manual row"});

    // 11. Restart streaming briefly to confirm startWrite can be toggled back on
    sdWriter::writeLabel(file, "restart write");
    sdWriter::startWrite(file);
    pros::Task writeTask2([file]() { sdWriter::writeData(file); }, "sdtest write 2");
    pros::delay(1000);
    sdWriter::stopWrite(file);
    pros::delay(200);

    sdWriter::writeLabel(file, "test end");

    printf("[sdtest] done. wrote ~%d rows to /usd/%s\n", counter, file.c_str());
}
