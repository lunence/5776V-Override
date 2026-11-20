#include "autonomous.hpp"

void skills() {
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
    chassis.moveDistance(-14, 1000, {.forwards = false});
    chassis.turnToHeading(90, 1000);
    chassis.moveDistance(14, 5000, {.maxSpeed = 70, .minSpeed = 20});
    leftMotors.move(0);
    rightMotors.move(0);

    // score preload
    liftTarget = 3;
    pros::delay(300); //TODO: take down delays here if possible
    clawState = 2;
    pros::delay(300);

    // get first pin stack
    chassis.moveDistance(-6, 1000, {.forwards = false, .minSpeed = 40}); //TODO: check ts
    liftTarget = -5; // not zero to get a little extra power going down
    clawState = 1;
    pros::delay(250); //TODO: REMOVE LATER
    chassis.distReset('F', 'R');
    chassis.turnToPoint(17, -27, 1000); //TODO: kinda slow exiting?
    chassis.moveDistance(15, 1000, {.minSpeed = 30}); //tune for speed
    chassis.moveToPoint(17, -27, 1000, {.maxSpeed = 30});
    leftMotors.move(0);
    rightMotors.move(0);
    pros::delay(200);

    // score pin stack 1
    liftTarget = 23; //TODO: tune
    chassis.turnToPoint(20, -45.5, 1000);
    chassis.moveToPoint(20, -45.5, 1000, {.maxSpeed = 70, .minSpeed = 20});
    liftTarget = 13;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);

    // get pin stack 2
    chassis.moveDistance(-10, 1000, {.forwards = false, .minSpeed = 40});
    clawState = 1;
    liftTarget = -5;
    chassis.turnToPoint(39, -46, 1000);
    chassis.moveDistance(18, 1000, {.minSpeed = 30});
    chassis.moveToPoint(39, -46, 1000, {.maxSpeed = 30});
    chassis.turnToHeading(270, 1000);
    chassis.distReset('B', 'L');

    return;

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


// void fourPinBack() {

//     // initialize
//     chassis.setPose(100, -100, 180);
//     chassis.distReset('L', 'F');

//     // toggle, lift dr4b
//     clawState = 3;
//     toggleState = 1;
//     pros::delay(600);
//     toggleState = 0;
//     liftTarget = 20;

//     // move to goal
//     chassis.moveDistance(-14, 1000, {.forwards = false});
//     chassis.turnToHeading(90, 1000);
//     chassis.moveDistance(18, 1000, {.maxSpeed = 60});

//     // score preload
//     liftTarget = 3;
//     pros::delay(400);
//     clawState = 2;
//     pros::delay(200);

//     // get first pin stack
//     chassis.moveDistance(-10, 1000, {.forwards = false});
//     clawState = 1;
//     pros::delay(300);
//     chassis.distReset('F', 'R');







//     return;
//     // chassis.turnToPoint(20, -24, 1000);
//     // // old(20, -24)
//     // chassis.moveToPoint(15,-29, 750, {.maxSpeed = 80, .earlyExitRange=1.5});
//     // //TODO: what the hell is this
//     // chassis.moveToPoint(24, -20, 750, {.maxSpeed = 30});
//     pros::delay(200);

//     // take the pin/cup and move up
//     liftTarget = 42;
//     chassis.turnToPoint(21, -42, 750);
//     chassis.moveToPoint(21, -42, 800, {.maxSpeed = 60});
//     liftTarget = 13;
//     pros::delay(400);
//     clawState = 2;
//     pros::delay(200);
//     // clawState = 1;

//     // back out and get the next pin
//     chassis.moveDistance(-17, 1000, {.forwards = false});
//     clawState=0;
//     liftTarget=1;
//     chassis.turnToHeading(135, 1000);
//     clawState=1;
//     chassis.moveToPoint(40, -41, 1000, {.maxSpeed = 60, .earlyExitRange=0.5});
//     chassis.moveToPoint(44.5, -46, 1000, {.maxSpeed = 20});
//     pros::delay(200);
//     chassis.turnToHeading(270, 1000);
//     chassis.distReset('B', 'L');

//     // take the pin/cup and score
//     liftTarget = 50;
//     pros::delay(400);
//     chassis.moveToPoint(21.5, -42, 1000, {.maxSpeed = 60});
//     // chassis.moveDistance(20, 1000, {.maxSpeed = 60});
//     liftTarget = 20;
//     pros::delay(500);
//     return;
// }

