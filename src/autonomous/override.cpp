#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void override() {
    // beginning turn
    // intakeState = 1;

    chassis.setPose(1, -1, 90);
    chassis.distanceReset('R', 'F');

    // get the first pin
    chassis.moveToPoint(94, -64, 1000);
    chassis.moveToPoint(110, -54, 1000);

    // turn to the next pin and get it
    chassis.turnToHeading(-45, 1000);
    chassis.moveToPoint(95, -30, 1000);

    //go to the quart
    chassis.turnToHeading(-90, 1000);
    chassis.moveToPoint(67.5, -30, 1500, {.minSpeed = 110, .earlyExitRange = 2});
    chassis.moveToPoint(40.5, -30, 1500, {.maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 2});
    
    // in the event it turns away from 90 consistently this is to adjust it
    chassis.turnToHeading(-90, 1000);

    chassis.moveDistance(-10, 1000, {.forwards = false});

    // wait a bit to calibrate
    pros::delay(350);

    // go to the wall to distreset
    chassis.turnToHeading(-50, 1000);
    chassis.moveDistance(48, 1000, {.minSpeed = 25, .earlyExitRange = 0.5});
    chassis.turnToHeading(0, 1000);

    // reset distance sensor 
    // chassis.distanceReset('L', 'B');

    // move to pin
    chassis.moveDistance(24.5, 1500);
    chassis.turnToHeading(-90, 1000);

    // align to line
    chassis.moveToPoint(10, 42, 1500);
    chassis.turnToHeading(135, 1000);

    // go to the center
    chassis.moveDistance(36, 1500);
    chassis.moveDistance(30, 1500);
}