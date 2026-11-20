#include "autonomous.hpp"

void mlCloseGoal(float prescore, float score) {
    //perform first ml
    chassis.moveToPose(65, -48, -90, 1000, {.forwards = false}, true);
    pros::delay(200); //TODO: tune
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToHeading(175, 1000); //TODO: see if this works
    chassis.moveDistance(13, 1000, {.maxSpeed = 90});
    liftTarget = 3; //lift up so stack doesn't drag
    pros::delay(200);
    
    //score first ml pin stack
    chassis.moveDistance(-13, 1000, {.forwards = false, .maxSpeed = 90});
    liftTarget = prescore;
    chassis.turnToHeading(-90, 1000);
    chassis.moveDistance(32, 1500, {.maxSpeed = 70, .minSpeed = 15}); //TODO: change maybe
    liftTarget = score;
    pros::delay(400);
    clawState = 2;
    chassis.distReset('B', 'L');
}

void skills() {
    overrideMotionLimits = true;

    
    // initialize
    chassis.setPose(100, -100, -90);
    /*
    chassis.distReset('L', 'F');

    // toggle and then lift dr4b
    clawState = 3;
    toggleState = 1;
    pros::delay(600);
    toggleState = 0;
    liftTarget = 17;

    // back out, turn and move to goal
    chassis.moveDistance(-14, 1000, {.forwards = false});
    chassis.turnToHeading(90, 1000);
    chassis.moveDistance(14, 1000, {.maxSpeed = 70, .minSpeed = 20}); //check to make sure

    // score preload
    liftTarget = 3;
    pros::delay(300);
    clawState = 2;
    pros::delay(300);
    leftMotors.move(0);
    rightMotors.move(0);

    // get first pin stack
    chassis.moveDistance(-6, 1000, {.forwards = false, .minSpeed = 40});
    liftTarget = -5; // not zero to get a little extra power going down
    clawState = 1;
    pros::delay(250); //TODO: remove when open claw doesn't block dsr
    chassis.distReset('F', 'R');
    chassis.turnToPoint(17.5, -27, 1000); //check exit here
    chassis.moveDistance(17, 1000, {.minSpeed = 20}); //tune for speed
    chassis.moveToPoint(17.5, -27, 1000, {.maxSpeed = 20});
    leftMotors.move(0);
    rightMotors.move(0);
    pros::delay(200);

    // score pin stack 1
    liftTarget = 27; //TODO: tune
    chassis.turnToPoint(20, -45.5, 1000);
    chassis.moveToPoint(20, -45.5, 1000, {.maxSpeed = 70, .minSpeed = 15});
    liftTarget = 11;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);

    // get pin stack 2
    chassis.moveDistance(-10, 1000, {.forwards = false, .minSpeed = 40});
    clawState = 1;
    liftTarget = -5;
    chassis.turnToPoint(39, -46, 1000); //prev 41 -48
    chassis.moveDistance(21, 1000, {.minSpeed = 20});
    chassis.moveToPoint(39, -46, 1000, {.maxSpeed = 20});
    chassis.turnToPoint(29, -47, 1000); //TODO: check, dsr might be off
    chassis.distReset('B', 'L');

    // score pin stack 2
    liftTarget = 42;
    pros::delay(400);
    chassis.moveToPoint(29, -47, 1000, {.maxSpeed = 70, .minSpeed = 15}); //TODO: verify
    liftTarget = 28;
    pros::delay(500);
    clawState = 2;
    chassis.distReset('B', 'L'); //TODO: if this acts funny it's bc claw hits dsr

    //two following pins
    mlCloseGoal(60, 43);
    mlCloseGoal(88, 62);

    */

    // ml first pin for second pin stack
    chassis.distReset('B', 'L'); //TODO: TEMPORARILY HERE FOR TESTING
    chassis.moveToPose(65, -48, -90, 1000, {.forwards = false}, true);
    pros::delay(200); //TODO: tune
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToHeading(175, 1000); //TODO: see if this works
    chassis.moveDistance(13, 1000, {.maxSpeed = 90});
    liftTarget = 5;
    pros::delay(200);

    // exit ml and score
    chassis.moveDistance(-10, 1000, {.forwards = false});
    chassis.distReset('L', 'F');
    liftTarget = 20;
    chassis.turnToPoint(51, -27, 1000);
    chassis.moveToPoint(51, -27, 1000, {.maxSpeed = 70, .minSpeed = 15});
    liftTarget = 3;
    pros::delay(500);
    clawState = 2;
    return;

    chassis.moveToPoint(65, -48, 1000, {.forwards = false});
    return;
}

/* LIFT HEIGHTS
 25 degrees prescore height pin 2
 11 degrees score height pin 2
 40 degrees prescore height pin 3
 28 degrees score height pin 3
 58.5 degrees prescore height pin 4
 43  degrees score height pin 4
 85.5 degrees prescore height pin 5
 62  degrees score height pin 5
 pin 6???
*/