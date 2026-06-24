#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void override() {
    // beginning turn
    // intakeState = 1;

    chassis.setPose(1, -1, 90);
    chassis.distanceReset('R', 'F');

    // get the first pin
    chassis.moveToPoint(94, -64, 1000, {.minSpeed = 100, .earlyExitRange= 0.5});
    chassis.moveToPoint(109, -54, 1000, {.minSpeed = 70, .earlyExitRange= 0.5});

    // turn to the next pin and get it
    chassis.turnToHeading(-42, 1000, {.minSpeed = 50});
    chassis.moveToPoint(93, -29, 1000, {.minSpeed = 70, .earlyExitRange= 0.5});

    //go to the quart
    chassis.turnToHeading(-97, 1000);
    chassis.moveToPoint(67.5, -27, 1500, {.minSpeed = 110, .earlyExitRange= 5});
    chassis.moveToPoint(47.5, -27, 1500, {.maxSpeed = 80, .minSpeed = 50, .earlyExitRange= 0.5});
    
    // in the event it turns away from 90 consistently this is to adjust it
    chassis.turnToHeading(-90, 1000);

    chassis.moveDistance(7, 1000);
    chassis.moveDistance(-10, 1000, {.forwards = false});

    // wait a bit to calibrate
    pros::delay(500);
    chassis.moveToPoint(12, -7, 1500);
    chassis.turnToHeading(0, 1000);

    // reset distance sensor 
    chassis.distanceReset('L', 'B');

    // get pin near wall
    chassis.turnToHeading(-21,1000);
    chassis.moveDistance(24.675, 1000, {.minSpeed = 12.5, .earlyExitRange= 0.5});
    chassis.turnToHeading(27, 500);

    // align to diagonal
    chassis.moveDistance(27,1000, {.minSpeed = 12.5, .earlyExitRange= 0.5});
    chassis.turnToHeading(135, 1000, {.minSpeed = 50});

    // get first pin, then second
    chassis.moveDistance(28, 1000, {.minSpeed = 80, .earlyExitRange=2});
    chassis.moveDistance(30, 1000, {.minSpeed = 90});
}