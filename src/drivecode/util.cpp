#include "drivecode/util.hpp"
#include "autonomous/autonSelector.hpp"
// #include "pros/misc.h"
// #include "pros/motors.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/objects.hpp"
#include "pros/screen.h"
#include "drivecode/cascade.hpp"
#include "drivecode/chainbar.hpp"
#include "drivecode/claw.hpp"

// initialize motors
void motorInit() {
    chainBar.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    cascadeFulls.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
    cascadeHalf.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
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
    pros::Task cascadeTask(runCascadeAuto, "cascade pid task");
    pros::Task chainbarTask(runChainBar, "chainbar pid task");
}

// // function to print motor voltages given a line to start on
// void printMotorVoltages(int line) {
//     pros::screen::print(pros::E_TEXT_SMALL, line+0, "leftFront: %d", leftFront.get_power());
//     // pros::screen::print(pros::E_TEXT_SMALL, line+1, "leftMid: %d", leftMid.get_power());
//     pros::screen::print(pros::E_TEXT_SMALL, line+2, "leftBack: %d", leftBack.get_power());
//     pros::screen::print(pros::E_TEXT_SMALL, line+3, "rightFront: %d", rightFront.get_power());
//     // pros::screen::print(pros::E_TEXT_SMALL, line+4, "rightMid: %d", rightMid.get_power());
//     pros::screen::print(pros::E_TEXT_SMALL, line+5, "rightBack: %d", rightBack.get_power());
// }

// print screen task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        // printMotorVoltages(0)

        pros::screen::print(pros::E_TEXT_SMALL, 0, "X: %.3f Y: %.3f Theta: %.3f", pose.x, pose.y, pose.theta);
        pros::screen::print(pros::E_TEXT_SMALL, 1, "cascade dist: %d", distCascade.get_distance());
        pros::screen::print(pros::E_TEXT_SMALL, 2, "claw state: %d", clawState);
        pros::screen::print(pros::E_TEXT_SMALL, 3, "chainbar state: %d", chainBarState);
        pros::screen::print(pros::E_TEXT_SMALL, 4, "chainbar rot: %.3f", chainBarRotation.get_position()/100.0);
        pros::screen::print(pros::E_TEXT_SMALL, 5, "target cb: %d", targetPos);


        // pros::screen::print(pros::E_TEXT_SMALL, 2, "cascadeState: %d", cascadeState);
        // pros::screen::print(pros::E_TEXT_SMALL, 3, "chainBarState: %d", chainBarState);
        // pros::screen::print(pros::E_TEXT_SMALL, 4, "resetState: %d", resetState);
        // pros::screen::print(pros::E_TEXT_SMALL, 5, "controlType: %d", controlType);

        // pros::screen::print(pros::E_TEXT_SMALL, 7, "rollerState: %d", rollerState);
        // pros::screen::print(pros::E_TEXT_SMALL, 8, "clawState: %d", clawState);

        // pros::screen::print(pros::E_TEXT_SMALL, 10, "incrementWorks3: %d", cascadePID_target);
        
        pros::delay(50);
    }
}

// gamepad task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}

