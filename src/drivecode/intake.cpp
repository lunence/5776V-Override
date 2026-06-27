// #include "lemlib/timer.hpp"
// #include "main.h"
// #include "pros/misc.h"
// #include "drivecode/intake.hpp"

// void runIntake() {
//     while (true) {
//         switch(intakeState) {
//             case 0: {
//                 break;
//             }

//             case 1: {
//                 break;
//             }

//             case 2: {
//                 break;
//             }
//         }
//     }
// }

// void updateIntake() {
//     if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
//         if (!intakePressed) {
//             if (toggleState == 3) {
//                 toggleState = 0;
//             } else {
//                 toggleState = 3;
//                 trapdoorState = 0;
//             }
//         }
//         intakePressed = true;
//     } else {
//         intakePressed = false;
//     }

//     // L2: outtake toggle
//     if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
//         if (!outtakePressed) {
//             if (toggleState == 2) {
//                 toggleState = 0;
//             } else {
//                 toggleState = 2;
//             }
//         }
//         outtakePressed = true;
//     } else {
//         outtakePressed = false;
//     }

//     // R1: hold override (scoring)
//     if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
//         intakeState = 1;
//         trapdoorState = 1;
//     } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { //Y hold override (mid goal score)
//         intakeState = 4;
//         trapdoorState = 0;
//     } else {
//         intakeState = toggleState; //update intake state to toggle state
//     }
// }