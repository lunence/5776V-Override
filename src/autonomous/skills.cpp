#include "autonomous.hpp"

void mlCloseGoal(float prescore, float score) {
    //perform ml
    chassis.moveToPoint(58, -48, 1000, {.forwards = false}, true); //prev x 65
    pros::delay(200); //TODO: tune
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToPoint(58, -59, 1000); //TODO: see if this works
    chassis.moveToPoint(58, -59, 1000, {.maxSpeed = 90});
    liftTarget = 3; //lift up so stack doesn't drag
    pros::delay(200);
    
    //score ml pin stack
    //TODO: replace movedistances maybe
    chassis.moveDistance(-12, 1000, {.forwards = false});
    liftTarget = prescore;
    chassis.turnToHeading(-90, 1000);
    chassis.moveDistance(30, 1500, {.maxSpeed = 80, .minSpeed = 15}); //TODO: old 32
    liftTarget = score;
    pros::delay(400); //TODO: score time?
    clawState = 2;
    chassis.distReset('B', 'L');
}

void mlFarGoal(float prescore, float score) {
    chassis.moveToPoint(55, -40, 1000, {.forwards = false, .maxSpeed = 90}, true); //TODO: REVIEW REVIEW
    pros::delay(400);
    clawState = 1;
    pros::delay(200);
    liftTarget = -5;
    chassis.waitUntilDone();

    chassis.turnToPoint(58, -59.5, 1000, {.maxSpeed = 100}); //TODO: see if this works
    chassis.distReset('L', 'F');
    chassis.moveToPoint(58, -59.5, 1000, {.maxSpeed = 90});
    liftTarget = 3;
    pros::delay(200);

    // exit ml and score first pin
    //prev 58
    chassis.moveToPoint(56, -45, 1000, {.forwards = false}); //TODO: this is not good but idc
    liftTarget = prescore;
    chassis.turnToPoint(50, -26, 1000);
    chassis.moveToPoint(50, -26, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = score;
    pros::delay(300);
    clawState = 2;
    
    // //perform ml, starting at goal
    // clawState = 2;
    // chassis.moveDistance(-10, 1000, {.forwards = false, .maxSpeed = 100}); //avoid claw closing early???
    // liftTarget = -5;
    // clawState = 1;
    // chassis.turnToPoint(58, -59, 2000); 
    // chassis.distReset('L', 'F');
    // chassis.moveToPoint(58, -59, 1000, {.maxSpeed = 90});
    // liftTarget = 3;

    // //score ml pin stack
    // chassis.moveToPoint(50, -39, 1000, {.forwards = false, .maxSpeed = 100}); //TODO: check 53
    // liftTarget = prescore;
    // chassis.turnToPoint(49, -24, 1000);
    // chassis.moveToPoint(49, -24, 1000, {.maxSpeed = 50, .minSpeed = 15});
    // liftTarget = score;
    // pros::delay(400);
    // clawState = 2;
}

//TODO: generally, might be going too fast into goals
void skills() {
    overrideMotionLimits = true;
    
    // initialize
    /*
    chassis.setPose(100, -100, 180);
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

    // get pin stack 1
    chassis.moveDistance(-6, 1000, {.forwards = false, .minSpeed = 40});
    liftTarget = -5; // not zero to get a little extra power going down
    clawState = 1;
    chassis.distReset('F', 'R');
    chassis.turnToPoint(20, -27, 1000); //TODO: exits slow
    chassis.moveDistance(21, 1000, {.minSpeed = 20}); //tune for speed //TODO: prev 18
    chassis.moveToPoint(20, -27, 1000, {.maxSpeed = 20});
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
    chassis.turnToPoint(47, -46, 1000);
    chassis.moveDistance(26, 1000, {.minSpeed = 20}); //TODO: prev 23
    chassis.moveToPoint(47, -46, 1000, {.maxSpeed = 20});
    chassis.turnToPoint(29, -48.5, 1000); 
    chassis.distReset('B', 'L');

    // score pin stack 2
    liftTarget = 42;
    pros::delay(400);
    chassis.moveToPoint(29, -48.5, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 28;
    pros::delay(500);
    clawState = 2;
    chassis.distReset('B', 'L');

    //two following pins
    mlCloseGoal(60, 43);
    mlCloseGoal(88, 62);
    */
    chassis.setPose(100, -100, -90);
    chassis.distReset('B', 'L');

    // ml first pin for second pin stack
    chassis.moveToPose(65, -48, -90, 1000, {.forwards = false}, true);
    pros::delay(400);
    clawState = 1;
    pros::delay(200);
    liftTarget = -5;
    chassis.waitUntilDone();

    chassis.turnToPoint(58, -59.5, 1000, {.maxSpeed = 100}); //TODO: see if this works
    chassis.distReset('L', 'F');
    chassis.moveToPoint(58, -59.5, 1000, {.maxSpeed = 90});
    liftTarget = 3;
    pros::delay(200);

    // exit ml and score first pin 2nd alliance goal
    chassis.moveToPoint(56, -45, 1000, {.forwards = false}); //TODO: this is not good but idc
    liftTarget = 20;
    chassis.turnToPoint(50, -26, 1000);
    chassis.moveToPoint(50, -26, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 3;
    pros::delay(300);
    clawState = 2;

    //next pins
    mlFarGoal(35, 20); //TODO: i lwk js added 3 to all lift heights
    // mlFarGoal(50, 35);
    // mlFarGoal(73, 50);

    // grab pin for center
    chassis.moveToPoint(55, -40, 1000, {.forwards = false, .maxSpeed = 90}, true); //TODO: REVIEW REVIEW
    pros::delay(400);
    clawState = 1;
    pros::delay(200);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToPoint(58, -59.5, 1000, {.maxSpeed = 100}); //TODO: see if this works
    chassis.distReset('L', 'F');
    chassis.moveToPoint(58, -59.5, 1000, {.maxSpeed = 90});
    liftTarget = 3;
    pros::delay(200);

    //leave for toggle
    chassis.moveToPose(60, -14, 180, 3000, {.forwards = false, .minSpeed = 50});
    chassis.moveToPose(55, 0, 90, 2000, {.forwards = false, .minSpeed = 30});
    chassis.turnToHeading(90, 1000, {.minSpeed = 30});
    toggleState = 1;
    pros::delay(600);
    toggleState = 0;
    chassis.moveDistance(-20, 1000, {.forwards = false});
    chassis.turnToHeading(-90, 1000);
    chassis.distReset('B', 'L');

    //go to center and score
    liftTarget = 20;
    chassis.moveToPoint(0, 0, 1000, {.maxSpeed = 80, .minSpeed = 20});
    liftTarget = 10;
    pros::delay(200);
    clawState = 2;
    return;
}

/* LIFT HEIGHTS PIN UP
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

/* LIFT HEIGHTS PIN DOWN*/