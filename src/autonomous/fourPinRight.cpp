#include "autonomous/autonomous.hpp"



void fourPinRight() {
    chassis.setPose(-1, -1, 90);
    chassis.distReset('F', 'R');

    // 
    toggleState = 1;
    pros::delay(500);
    toggleState = 0;
    chassis.moveToPoint(-23, -50, 1000, {}, true);
    manualLiftState = 1;
    pros::delay(250);
    chassis.waitUntilDone();
    manualLiftState = 3;
    pros::delay(300);
    clawState = 2;

    manualLiftState = 0;
    chassis.moveDistance(-20, 1000, {.forwards = false});
    chassis.turnToHeading(45, 1000);
    clawState = 1;
    chassis.moveToPoint(-22, -26, 1000, {.maxSpeed = 40});
    pros::delay(100);
    clawState = 2;

    chassis.turnToHeading(180, 1000);
    chassis.moveDistance(20, 1000, {}, true);
    manualLiftState = 1;
    pros::delay(500);
    chassis.waitUntilDone();
    manualLiftState = 2;
    pros::delay(650);
    clawState = 2;

    manualLiftState = 0;
    chassis.moveDistance(-20, 1000, {.forwards = false});
    chassis.turnToHeading(135, 1000);
    clawState = 1;
    chassis.moveToPoint(-22, -26, 1000, {.maxSpeed = 40});
    pros::delay(100);
    clawState = 2;

    chassis.turnToHeading(-90, 1000);
    chassis.moveDistance(20, 1000, {}, true);
    manualLiftState = 1;
    pros::delay(500);
    chassis.waitUntilDone();
    manualLiftState = 2;
    pros::delay(650);
    clawState = 2;

    pros::delay(500);
    clawState = 0
    manualLiftState = 0;

}