#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void override() {
    // beginning turn
    // intakeState = 1;

    chassis.setPose(1, -1, 90);
    chassis.distanceReset('R', 'F');

    // get the first pin
    chassis.moveToPoint(94, -64, 750, {.minSpeed = 80, .earlyExitRange = 0.8});
    chassis.moveToPoint(110, -54, 750);

    // turn to the next pin and get it
    chassis.turnToHeading(-45, 650);
    chassis.moveToPoint(95, -30, 1500, {.minSpeed = 80});

    //go to the quart
    chassis.turnToHeading(-90, 600);
    chassis.moveToPoint(67.5, -30, 1000, {.minSpeed = 110, .earlyExitRange = 2});
    chassis.moveToPoint(40.5, -30, 800, {.maxSpeed = 50, .minSpeed = 40});
    
    // in the event it turns away from 90 consistently this is to adjust it
    chassis.turnToHeading(-90, 1000);

    chassis.moveDistance(-10, 750, {.forwards = false, .minSpeed = 95});

    // wait a bit to calibrate
    pros::delay(350);

    // go to the wall to distreset
    chassis.turnToHeading(-50, 800);
    chassis.moveDistance(48, 1000, {.minSpeed = 75, .earlyExitRange = 0.5});
    chassis.turnToHeading(5, 600);

    // reset distance sensor 
    // chassis.distanceReset('L', 'B');

    // move to pin
    chassis.moveDistance(24.5, 1000);
    chassis.turnToHeading(-90, 600);
    chassis.moveDistance(5, 300, {.minSpeed = 80});
    chassis.moveDistance(-5, 300, {.forwards = false});
    chassis.turnToHeading(0, 600);

    // align to line
    chassis.moveToPoint(10, 45, 800);
    chassis.turnToHeading(133, 850);

    // go to the center
    chassis.moveDistance(36, 1500, {.maxSpeed = 80, .earlyExitRange = 2});

    chassis.turnToHeading(133, 850);

    chassis.moveDistance(30, 1500, {.minSpeed = 100});
}