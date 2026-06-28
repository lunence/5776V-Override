#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"

void runCascade();

void motorInit() {
    cascadeL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    cascadeR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chainBar.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
    // pros::Task sdWriteTask(sdWriter::runWriter, "sd write task");
    pros::Task cascadeTask(runCascade, "cascade task");
    pros::Task intakeTask(runIntake, "intake task");
    pros::Task pistonTask(runPistons, "pistons task");
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