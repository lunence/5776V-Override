#include "drivecode/util.hpp"
// #include "drivecode/claw.hpp"

// initialize motors
void motorInit() {
    reversebar.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
}

// sensor settings
void sensorInit() {
    liftRotation.set_position(0);
}

// begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
    pros::Task consoleTask(runConsole, "console task");

    // pros::Task manualClawTask(runClaw, "manual claw task");
}

// print screen task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_SMALL, 0, "X: %.3f Y: %.3f Theta: %.3f", pose.x, pose.y, pose.theta);

        pros::delay(10);
    }
}

// gamepad task
void runConsole() {
    while(true) {
        pros::delay(10);
    }
}