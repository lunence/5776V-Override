#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"
#include "drivecode/cascade.hpp"

void runCascade();

void motorInit() {
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
    // pros::Task sdWriteTask(sdWriter::runWriter, "sd write task");
    pros::Task cascadeTask(runCascade, "cascade task");
}

//brain task
void runScreen() {
    while(true) {
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Cascade State: %d", cascadeState);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "DistSensor: %.3f", distCascade.get());

        pros::delay(10);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}