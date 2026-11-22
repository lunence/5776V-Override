#include "autonomous.hpp"

void preloadRight() {
    chassis.setPose(100, 100, -90);
    chassis.distReset('B', 'R'); 

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(450);
    toggleState = 0;
    liftTarget = 20;

    // back out, turn and move to goal
    // chassis.moveToPoint(3, -47, 1000, {.forwards = false});
    // chassis.turnToPoint(18, -47, 1000, {.minSpeed = 20}); //TODO: minspeed 20
    // chassis.moveToPoint(18, -47, 1000, {.maxSpeed = 70, .minSpeed = 30});
    chassis.moveDistance(-14, 1000, {.forwards = false});
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(14, 1000, {.maxSpeed = 70, .minSpeed = 20}); //check to make sure

    // score preload
    liftTarget = 3;
    pros::delay(300);
    clawState = 2;
    pros::delay(300);
    leftMotors.move(0);
    rightMotors.move(0);
}