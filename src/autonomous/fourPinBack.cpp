#include "autonomous.hpp"

void fourPinBack() {
overrideMotionLimits = true;
    // initialize
    chassis.setPose(100, -100, 180);
    chassis.distReset('L', 'F');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(650);
    toggleState = 0;
    liftTarget = 20;

    // back out, turn and move to goal
    chassis.moveToPoint(3, -48, 1000, {.forwards = false});
    chassis.turnToPoint(19, -48, 1000);
    chassis.moveToPoint(19, -48, 1000, {.maxSpeed = 60, .minSpeed = 20});

    // score preload
    liftTarget = 4;
    pros::delay(600);
    clawState = 2;
    pros::delay(400);
    leftMotors.move(0);
    rightMotors.move(0);

    // get pin stack 1
    //prev x 10
    chassis.moveToPose(5, -46, 95, 1000, {.forwards = false}, true); //curve away
    pros::delay(400);
    clawState = 1;
    chassis.waitUntilDone();
    chassis.distReset('F', 'R');
    liftTarget = -5;
    chassis.turnToPoint(18, -27, 1000);
    chassis.moveDistance(19, 1000, {.minSpeed = 20});
    chassis.moveToPoint(18, -27, 1000, {.maxSpeed = 20});
    leftMotors.move(0);
    rightMotors.move(0);
    pros::delay(200);

    // score pin stack 1
    liftTarget = 27;
    chassis.turnToPoint(23, -44, 1000);
    chassis.moveToPoint(23, -44, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 11;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);

    // get pin stack 2
    chassis.moveDistance(-10, 1000, {.forwards = false, .minSpeed = 40});
    clawState = 1;
    liftTarget = -5;
    chassis.turnToPoint(45, -45, 1000, {.minSpeed = 15});
    chassis.moveDistance(24, 1000, {.minSpeed = 20}); //TODO: prev 23
    chassis.moveToPoint(45, -45, 1000, {.maxSpeed = 20});
    chassis.turnToPoint(29, -48.5, 1000); 
    chassis.distReset('B', 'L');

    // score pin stack 2
    liftTarget = 45;
    pros::delay(400);
    chassis.moveToPoint(29, -48.5, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 28;
    pros::delay(500);
    clawState = 2;
    chassis.distReset('B', 'L');
}