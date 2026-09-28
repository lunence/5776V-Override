#include "drivecode/util.hpp"
#include "autonomous/autonSelector.hpp"
// #include "pros/misc.h"
// #include "pros/motors.h"
#include "lemlib/util.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/objects.hpp"
#include "pros/screen.h"
#include "drivecode/claw.hpp"
#include "drivecode/dr4b.hpp"

// initialize motors
void motorInit() {
    // chainBar.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
    // cascadeFulls.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
    // cascadeHalf.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
    reversebar.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
}

// sensor settings
void sensorInit() {
    cascadeRotation.set_position(0);
    chainBarRotation.set_position(0);

    // vision.clear_led();
    // vision.set_exposure(150);
    // vision.set_led(4024241);

    // vision.set_signature(0, &yellowSig);
    // vision.set_signature(0, &blueSig);
    // vision.set_signature(0, &redSig);
}

// begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
    pros::Task consoleTask(runConsole, "console task");

    pros::Task manualClawTask(runClaw, "manual claw task");
    pros::Task macroLiftTask(macroLift, "macro lift task");
    pros::Task manualLiftTask(runLift, "manual lift task");
}

// print screen task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_SMALL, 0, "X: %.3f Y: %.3f Theta: %.3f", pose.x, pose.y, pose.theta);
        pros::screen::print(pros::E_TEXT_SMALL, 1, "lift state: %d", liftMacroState);
        pros::screen::print(pros::E_TEXT_SMALL, 2, "lift distance: %.2f", lemlib::mmToIn(distLift.get_distance()));
        pros::screen::print(pros::E_TEXT_SMALL, 3, "lift optical: %.3f", goalOptical.get_hue());
        pros::screen::print(pros::E_TEXT_SMALL, 4, "manual lift state: %d", manualLiftState);
        pros::screen::print(pros::E_TEXT_SMALL, 5, "manual lifting: %d", manualControl);

        pros::delay(50);
    }
}

// gamepad task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}