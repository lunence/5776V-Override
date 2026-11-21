#include "autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void mlCloseGoal(float prescore, float score) {
    //perform ml
    chassis.moveToPoint(58, -48, 1000, {.forwards = false}, true); //prev x 65
    pros::delay(300); //TODO: tune
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToPoint(58, -59, 1000);
    chassis.moveToPoint(58, -59, 1000, {.minSpeed = 40}); //TODO: min speed 40
    liftTarget = 3; //lift up so stack doesn't drag
    pros::delay(200);
    
    //score ml pin stack
    //TODO: replace movedistances maybe
    chassis.moveDistance(-13.5, 1000, {.forwards = false}); //TODO: prev 12
    liftTarget = prescore;
    chassis.turnToHeading(-90, 1000);
    chassis.moveDistance(32, 1500, {.maxSpeed = 70, .minSpeed = 10}); //TODO: old minspeed 20
    liftTarget = score;
    pros::delay(400); //TODO: score time 400
    clawState = 2;
    chassis.distReset('B', 'L');
}

void mlFarGoal(float prescore, float score) {
    chassis.moveToPoint(55, -40, 1000, {.forwards = false}, true); //TODO: REVIEW REVIEW
    pros::delay(600);
    clawState = 1;
    pros::delay(200);
    liftTarget = -5;
    chassis.waitUntilDone();

    chassis.turnToHeading(180, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE,.minSpeed = 40}); //TODO: this needs to be here for the dist reset statement
    chassis.distReset('L', 'F'); //TODO: swapped with dist reset statement below
    chassis.turnToPoint(58.5, -59.5, 1000); //TODO: no minSpeed, old minSpeed 30
    // chassis.distReset('L', 'F');
    chassis.moveToPoint(58.5, -59.5, 1000, {.minSpeed = 40});
    liftTarget = 5;
    pros::delay(300); //TODO: increased collect time from 200 to 400

    // exit ml and score
    chassis.moveToPoint(56, -45, 1000, {.forwards = false}); //TODO: max speed 100?
    liftTarget = prescore;
    chassis.turnToPoint(49, -26, 1000);
    chassis.moveToPoint(49, -26, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = score;
    pros::delay(200); //TODO: score time 400
    clawState = 2;
}

void skills() {
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
    chassis.turnToPoint(18, -47, 1000);
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
    chassis.turnToPoint(19, -27, 1000);
    chassis.moveDistance(21, 1000, {.minSpeed = 20});
    chassis.moveToPoint(19, -27, 1000, {.maxSpeed = 20});
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
    chassis.turnToPoint(45, -45, 1000);
    chassis.moveDistance(26, 1000, {.minSpeed = 20}); //TODO: prev 23
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

    //two following pins
    mlCloseGoal(60, 43);
    mlCloseGoal(88, 62);
    chassis.distReset('B', 'L');

    // ml first pin for second pin stack
    //TODO: dropped by an inch from 65
    chassis.moveToPose(64, -48, -90, 1000, {.forwards = false}, true);
    pros::delay(400);
    clawState = 1;
    pros::delay(200);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.distReset('B', 'L');

    chassis.turnToPoint(57, -59.5, 1000, {.maxSpeed = 100});
    chassis.moveToPoint(57, -59.5, 1000, {.minSpeed = 40});
    liftTarget = 3;
    pros::delay(200);

    // exit ml and score first pin 2nd alliance goal
    chassis.moveToPoint(56, -45, 1000, {.forwards = false});
    liftTarget = 20;
    chassis.turnToPoint(48, -26, 1000);
    chassis.moveToPoint(48, -26, 1000, {.maxSpeed = 80, .minSpeed = 15});
    liftTarget = 3;
    pros::delay(400);
    clawState = 2;

    //next pins
    mlFarGoal(35, 25); 
    mlFarGoal(55, 45);
    mlFarGoal(75, 65);

    // grab pin for center
    chassis.moveToPoint(55, -40, 1000, {.forwards = false}, true); //TODO: REVIEW REVIEW
    pros::delay(600);
    clawState = 1;
    pros::delay(200);
    liftTarget = -5;
    chassis.waitUntilDone();

    chassis.turnToHeading(180, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE,.minSpeed = 40}); //TODO: this needs to be here for the dist reset statement
    chassis.distReset('L', 'F'); //TODO: swapped with dist reset statement below
    chassis.turnToPoint(58.5, -59.5, 1000); //TODO: see if this works
    // chassis.distReset('L', 'F');
    chassis.moveToPoint(58.5, -59.5, 1000, {.minSpeed = 40});
    liftTarget = 5;
    pros::delay(300); //TODO: increased collect time from 200 to 400

    //leave for toggle
    chassis.moveToPose(60, -14, 180, 3000, {.forwards = false, .minSpeed = 50});
    chassis.moveToPose(55, 0, 90, 2000, {.forwards = false, .minSpeed = 30});
    chassis.turnToHeading(90, 1000, {.minSpeed = 30});
    toggleState = 1;
    leftMotors.move(40);
    rightMotors.move(40);
    pros::delay(300);
    leftMotors.move(0);
    rightMotors.move(0);
    pros::delay(400);
    toggleState = 0;
    chassis.moveDistance(-25, 1000, {.forwards = false});
    chassis.distReset('F', 'R');
    chassis.turnToPoint(0, 0, 1000);

    //go to center and score
    liftTarget = 35;
    chassis.moveToPoint(-3, 0, 1500, {.maxSpeed = 70, .minSpeed = 15});
    liftTarget = 20;
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