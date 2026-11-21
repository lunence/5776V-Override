#include "autonomous.hpp"

void fourPinBack() {

    overrideMotionLimits = true;
    // initialize
    chassis.setPose(100, -100, 180);
    chassis.distReset('L', 'F');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(600);
    toggleState = 0;
    liftTarget = 20;

    // back out, turn and move to goal
    chassis.moveToPoint(3, -47, 1000, {.forwards = false});
    chassis.turnToPoint(18, -47, 1000, {.minSpeed = 20}); //TODO: minspeed 20
    chassis.moveToPoint(18, -47, 1000, {.maxSpeed = 70, .minSpeed = 30});

    // score preload
    liftTarget = 3;
    pros::delay(300);
    clawState = 2;
    pros::delay(300);
    leftMotors.move(0);
    rightMotors.move(0);

    // get pin stack 1
    //prev x 10
    chassis.moveToPose(5, -46, 95, 1000, {.forwards = false, .minSpeed = 40}, true); //TODO: try curve away
    pros::delay(200);
    clawState = 1;
    chassis.waitUntilDone();
    chassis.distReset('F', 'R'); //TODO: blocked by claw?
    liftTarget = -5;
    chassis.turnToPoint(19, -27, 1000, {.minSpeed = 15}); //TODO: minspeed 15
    chassis.moveDistance(21, 1000, {.minSpeed = 20});
    chassis.moveToPoint(19, -27, 1000, {.maxSpeed = 20, .minSpeed = 10});
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
    chassis.moveDistance(26, 1000, {.minSpeed = 20}); //TODO: prev 23
    chassis.moveToPoint(45, -45, 1000, {.maxSpeed = 20, .minSpeed = 10});
    chassis.turnToPoint(29, -48.5, 1000); 
    chassis.distReset('B', 'L');

    // score pin stack 2
    liftTarget = 45;
    pros::delay(400);
    chassis.moveToPoint(29, -48.5, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 28;
    pros::delay(500);
    clawState = 2;
}