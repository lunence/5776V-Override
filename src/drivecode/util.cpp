#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"

void motorInit() {
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %.3f", pose.theta);
        
        pros::delay(50);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}