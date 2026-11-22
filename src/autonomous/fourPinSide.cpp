#include "autonomous/autonomous.hpp"
//reflected four pin back

void fourPinSide() {
overrideMotionLimits = true;
    // initialize
    chassis.setPose(100, -100, 90);
    chassis.distReset('F', 'R');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(650);
    toggleState = 0;
    liftTarget = 20;

    // back out, turn and move to goal
    chassis.moveToPoint(48, -3, 1000, {.forwards = false, .minSpeed = 20});
    chassis.turnToPoint(48, -19, 1000);
    chassis.moveToPoint(48, -19, 1000, {.maxSpeed = 60, .minSpeed = 20});

    // score preload
    liftTarget = 4;
    pros::delay(500); // TODO: Previously 600
    clawState = 2;
    pros::delay(400);
    leftMotors.move(0);
    rightMotors.move(0);

    // get pin stack 1
    //prev x 10
    // chassis.moveToPose(46, -5, 190, 1000, {.forwards = false}, true); //curve away
    chassis.moveDistance(-10, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 3});
    pros::delay(400);
    clawState = 1;
    chassis.waitUntilDone();
    chassis.distReset('L', 'F');
    liftTarget = -5;
    chassis.turnToPoint(27, -19, 1000);
    chassis.moveDistance(19, 1000, {.minSpeed = 20});
    chassis.moveToPoint(27, -19, 1000, {.maxSpeed = 20, .earlyExitRange=5});
    leftMotors.move(0);
    rightMotors.move(0);
    pros::delay(200);

    // score pin stack 1
    liftTarget = 27;
    chassis.turnToPoint(44, -23, 1000);
    chassis.moveToPoint(44, -23, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 11;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);

    // get pin stack 2
    chassis.moveDistance(-10, 1000, {.forwards = false, .minSpeed = 40});
    clawState = 1;
    liftTarget = -5;
    chassis.turnToPoint(46, -45, 1000, {.minSpeed = 15});
    chassis.moveDistance(24, 1000, {.minSpeed = 20}); //TODO: prev 23
    chassis.moveToPoint(46, -45, 1000, {.maxSpeed = 20, .earlyExitRange = 3}, true); // TODO: added earlyeaxitrange of 3
    pros::delay(500);
    liftTarget = 47;
    chassis.turnToPoint(48.5, -29, 1000); 
    chassis.distReset('R', 'B');

    // score pin stack 2
    // liftTarget = 47;
    // pros::delay(450); //TODO: previously 400
    chassis.moveToPoint(48.5, -29, 1000, {.maxSpeed = 80, .minSpeed = 15}, true);
    pros::delay(100);
    liftTarget = 28;
    pros::delay(500);
    clawState = 2;
}