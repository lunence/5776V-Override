#include "autonomous.hpp"

void fourPinBack() {

    // initialize
    chassis.setPose(100, -100, 180);
    chassis.distReset('L', 'F');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(800);
    toggleState = 0;
    liftTarget = 20;

    // back out, turn and move to goal
    chassis.moveDistance(-14, 1000, {.forwards = false});
    chassis.turnToHeading(90, 1000);
    chassis.moveDistance(18, 1000, {.maxSpeed = 60});

    // send voltage to drive while scoring
    liftTarget = 3;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);

    // back out, turn and get next pin
    chassis.moveDistance(-10, 1000, {.forwards = false});
    clawState = 1;
    chassis.distReset('F', 'R');
    chassis.turnToPoint(20, -24, 1000);
    chassis.moveToPoint(20, -24, 1000, {.maxSpeed = 60});
    pros::delay(200);

    // take the pin/cup and move up
    liftTarget = 25;
    chassis.turnToPoint(21, -41.5, 1000);
    chassis.moveToPoint(21, -41.5, 1000, {.maxSpeed = 60});
    liftTarget = 15;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);
    // clawState = 1;
    return;
}