#include "autonomous.hpp"

void fourPinBack() {

    // initialize
    chassis.setPose(100, -100, 180);
    chassis.distReset('L', 'F');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(400);
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
    // old(20, -24)
    chassis.moveToPoint(15,-29, 750, {.maxSpeed = 80, .earlyExitRange=1.5});
    chassis.moveToPoint(24, -20, 750, {.maxSpeed = 30});
    pros::delay(200);

    // take the pin/cup and move up
    liftTarget = 42;
    chassis.turnToPoint(21, -42, 750);
    chassis.moveToPoint(21, -42, 800, {.maxSpeed = 60});
    liftTarget = 13;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);
    // clawState = 1;

    // back out and get the next pin
    chassis.moveDistance(-17, 1000, {.forwards = false});
    clawState=0;
    liftTarget=1;
    chassis.turnToHeading(135, 1000);
    clawState=1;
    chassis.moveToPoint(40, -41, 1000, {.maxSpeed = 60, .earlyExitRange=0.5});
    chassis.moveToPoint(44.5, -46, 1000, {.maxSpeed = 20});
    pros::delay(200);
    chassis.turnToHeading(270, 1000);
    chassis.distReset('B', 'L');

    // take the pin/cup and score
    liftTarget = 50;
    pros::delay(400);
    chassis.moveToPoint(21.5, -42, 1000, {.maxSpeed = 60});
    // chassis.moveDistance(20, 1000, {.maxSpeed = 60});
    liftTarget = 20;
    pros::delay(500);
    return;
}

void skills() {

    // initialize
    chassis.setPose(100, -100, 180);
    chassis.distReset('L', 'F');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(400);
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
    // old(20, -24)
    chassis.moveToPoint(15,-29, 750, {.maxSpeed = 80, .earlyExitRange=1.5});
    chassis.moveToPoint(24, -20, 750, {.maxSpeed = 30});
    pros::delay(200);

    // take the pin/cup and move up
    liftTarget = 42;
    chassis.turnToPoint(21, -42, 750);
    chassis.moveToPoint(21, -42, 800, {.maxSpeed = 60});
    liftTarget = 13;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);
    // clawState = 1;

    // back out and get the next pin
    chassis.moveDistance(-17, 1000, {.forwards = false});
    clawState=0;
    liftTarget=1;
    chassis.turnToHeading(135, 1000);
    clawState=1;
    chassis.moveToPoint(40, -41, 1000, {.maxSpeed = 60, .earlyExitRange=0.5});
    chassis.moveToPoint(44.5, -46, 1000, {.maxSpeed = 20});
    pros::delay(200);
    chassis.turnToHeading(270, 1000);
    chassis.distReset('B', 'L');

    // take the pin/cup and score
    liftTarget = 50;
    pros::delay(400);
    chassis.moveToPoint(21.5, -42, 1000, {.maxSpeed = 60});
    // chassis.moveDistance(20, 1000, {.maxSpeed = 60});
    liftTarget = 20;
    pros::delay(500);
    
    
    // SKILLLSS
    clawState = 2;
    chassis.moveDistance(-25, 1000, {.forwards = false});
    chassis.turnToHeading(90, 1000);
}