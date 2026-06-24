#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void override() {
    // beginning turn
    // intakeState = 1;

    chassis.setPose(1, -1, 90);
    chassis.distanceReset('R', 'F');

    // get the first pin
    chassis.moveToPoint(94, -64, 1000);
    chassis.moveToPoint(110, -55.5, 1000);

    // turn to the next pin and get it
    chassis.turnToHeading(-42, 1000);
    chassis.moveToPoint(95, -30, 1000);

    //go to the quart
    chassis.turnToHeading(-90, 1000);
    chassis.moveToPoint(67.5, -30, 1500);
    chassis.moveToPoint(40.5, -30, 1500);
    
    // in the event it turns away from 90 consistently this is to adjust it
    chassis.turnToHeading(-90, 1000);

    chassis.moveDistance(-10, 1000, {.forwards = false});

    // wait a bit to calibrate
    pros::delay(350);

    // go to the wall to distreset
    chassis.moveToPoint(90, 90, 1500);
    chassis.turnToHeading(0, 1000);

    // reset distance sensor 
    chassis.distanceReset('L', 'B');

    // // get pin near wall
    // chassis.turnToHeading(-21, 1000);
    // chassis.moveDistance(24.675, 1000, {.minSpeed = 12.5, .earlyExitRange= 0.5});
    // chassis.turnToHeading(27, 500);

    // // align to diagonal
    // chassis.moveDistance(27,1000, {.minSpeed = 12.5, .earlyExitRange= 0.5});
    // chassis.turnToHeading(135, 1000, {.minSpeed = 50});

    // // get first pin, then second
    // chassis.moveDistance(28, 1000, {.minSpeed = 80, .earlyExitRange=2});
    // chassis.moveDistance(30, 1000, {.minSpeed = 90});
}