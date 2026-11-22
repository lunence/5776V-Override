#include "autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void mlCloseGoal(float prescore, float score) {
    chassis.moveToPoint(58, -48, 1000, {.forwards = false}, true); //prev x 65
    pros::delay(300); //TODO: tune
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToPoint(58, -59, 1000);
    chassis.moveToPoint(58, -59, 1000, {.minSpeed = 40}); //TODO: min speed 40
    pros::delay(500); //collect time 500

    chassis.moveToPoint(58, -49, 1500, {.forwards = false});
    liftTarget = prescore;
    chassis.turnToPoint(28, -47, 1000); //TODO: check these, used to be -47 48
    chassis.moveToPoint(28, -47, 2000, {.maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 2});
    liftTarget = score;
    pros::delay(400);
    clawState = 2;
    pros::delay(200);
    chassis.distReset('B', 'L');
    // //perform ml
    // chassis.moveToPoint(58, -48, 1000, {.forwards = false}, true); //prev x 65
    // pros::delay(300); //TODO: tune
    // clawState = 1;
    // pros::delay(400);
    // liftTarget = -5;
    // chassis.waitUntilDone();
    // chassis.turnToPoint(58, -59, 1000);
    // chassis.moveToPoint(58, -59, 1000, {.minSpeed = 40}); //TODO: min speed 40
    // liftTarget = 3; //lift up so stack doesn't drag
    // pros::delay(200);
    
    // //score ml pin stack
    // //TODO: replace movedistances maybe
    // chassis.moveDistance(-13.5, 1000, {.forwards = false}); //TODO: prev 12
    // liftTarget = prescore;
    // chassis.turnToHeading(-90, 1000);
    // //TODO: from 32 to 31, maxspeed 100
    // chassis.moveDistance(31, 1500, {.maxSpeed = 70}); //TODO: old minspeed 20, earlyExitRange?
    // liftTarget = score;
    // pros::delay(400); //TODO: score time 400
    // clawState = 2;
    // chassis.distReset('B', 'L');
}

void mlFarGoal(float prescore, float score) {
    chassis.moveToPoint(60, -48, 1000, {.forwards = false}, true); //prev x 65
    pros::delay(300);
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(58, -59, 1000, {.minSpeed = 40}); //TODO: min speed 40
    pros::delay(500); //collect time 500

    liftTarget = 3;
    chassis.moveToPoint(58, -47, 1000, {.forwards = false}); //reverse out
    chassis.distReset('L', 'F'); //TODO: DIST RESET AFTER REVERSE
    liftTarget = prescore;
    chassis.turnToPoint(51, -27, 1000); //TODO: good coord?
    chassis.moveToPoint(51, -27, 1000, {.maxSpeed = 60, .minSpeed = 20}); //TODO: does eer work
    liftTarget = score;
    pros::delay(400);
    clawState = 2;
    pros::delay(400);

    
    // chassis.moveToPoint(55, -40, 1000, {.forwards = false}, true); //TODO: REVIEW REVIEW
    // pros::delay(600);
    // clawState = 1;
    // pros::delay(200);
    // liftTarget = -5;
    // chassis.waitUntilDone();

    // chassis.turnToHeading(180, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE,.minSpeed = 40}); //TODO: this needs to be here for the dist reset statement
    // chassis.distReset('L', 'F'); //TODO: swapped with dist reset statement below
    // chassis.turnToPoint(58.5, -59.5, 1000); //TODO: minSpeed 20
    // // chassis.distReset('L', 'F');
    // chassis.moveToPoint(58.5, -59.5, 1000, {.minSpeed = 40});
    // liftTarget = 5;
    // pros::delay(350); //TODO: increased collect time from 200 to 400

    // // exit ml and score
    // chassis.moveToPoint(56, -45, 1000, {.forwards = false}); //TODO: max speed 100?
    // liftTarget = prescore;
    // chassis.turnToPoint(49, -26, 1000);
    // chassis.moveToPoint(49, -26, 1000, {.maxSpeed = 70, .minSpeed = 15});
    // liftTarget = score;
    // pros::delay(200); //TODO: score time 400
    // clawState = 2;
}

void skills() {
    
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

    //+2 pin stacks from ml
    mlCloseGoal(65, 45);
    mlCloseGoal(88, 62);

    //TODO: test reset
    // chassis.setPose(100, -100, -90);
    // chassis.distReset('B', 'L');

    chassis.moveToPoint(58, -48, 1000, {.forwards = false}, true); //prev x 65
    pros::delay(300);
    clawState = 1;
    pros::delay(400);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(58, -59, 1000, {.minSpeed = 40}); //TODO: min speed 40
    pros::delay(500); //collect time 500
    liftTarget = 3;

    chassis.moveToPoint(58, -47, 1000, {.forwards = false}); //reverse out
    chassis.distReset('L', 'F'); //TODO: DIST RESET AFTER REVERSE
    liftTarget = 20;
    chassis.turnToPoint(49.5, -30, 1000);
    chassis.moveToPoint(49.5, -30, 1000, {.maxSpeed = 60, .minSpeed = 20}); //TODO: does eer work
    liftTarget = 5;
    pros::delay(300);
    clawState = 2;
    pros::delay(500);

    mlFarGoal(45, 25);
    mlFarGoal(65, 55);

    chassis.moveToPose(62, -42, 0, 1500, {.forwards = false}, true);
    pros::delay(300);
    liftTarget = -5;
    chassis.waitUntilDone();
    chassis.moveToPoint(62, -4, 1500, {.minSpeed = 80});
    chassis.turnToHeading(90, 1000);
    toggleState = 1;
    leftMotors.move(40);
    rightMotors.move(40);
    pros::delay(600);
    leftMotors.move(0);
    rightMotors.move(0);
    chassis.moveDistance(-60, 1000, {.forwards = false, .minSpeed = 100});


    // // grab pin for center

    // //leave for toggle
    // chassis.moveToPose(60, -14, 0, 3000, {.forwards = false}); //old minSpeed 50
    // chassis.moveToPose(55, 0, 90, 2000, {.forwards = false, .minSpeed = 40});
    // chassis.turnToHeading(90, 1000, {.minSpeed = 30});
    // toggleState = 1;
    // leftMotors.move(40);
    // rightMotors.move(40);
    // pros::delay(300);
    // leftMotors.move(0);
    // rightMotors.move(0);
    // pros::delay(300);
    // toggleState = 0;
    // chassis.moveDistance(-25, 1000, {.forwards = false, .minSpeed = 100});
    // chassis.distReset('F', 'R');
    // chassis.turnToPoint(0, 0, 1000, {.minSpeed = 20});

    // //go to center and score
    // liftTarget = 35;
    // chassis.moveToPoint(-3, 0, 1500, {.minSpeed = 40}, true);
    // pros::delay(400);
    // liftTarget = 20;
    // pros::delay(200);
    // clawState = 2;
    // chassis.waitUntilDone();
    // return;
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