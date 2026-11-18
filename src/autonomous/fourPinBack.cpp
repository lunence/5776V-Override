#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void wallPin() {
    //L unreliable

    // reset
    chassis.setPose(100, -100, 90); //guarantees second quadrant reset

    // toggle
    clawState = 3; //begin low intake preload
    toggleState = 1;
    pros::delay(1000);
    toggleState = 0;

    //bring lift up
    manualLiftState = 1;
    pros::delay(300);
    manualLiftState = 0;

    // position preload
    chassis.moveDistance(-16, 1000, {.forwards = false});
    chassis.turnToHeading(180, 1000, {.maxSpeed = 100}); //TODO: check max speed 100

    // move to score preload
    chassis.moveDistance(22, 1000, {.maxSpeed = 60}, true);
    manualLiftState = 1;
    pros::delay(300);
    manualLiftState = 0;
    chassis.waitUntilDone();
    chassis.distReset('L', 'F');

    // score preload
    manualLiftState = 4;
    pros::delay(650);
    clawState = 2;
    manualLiftState = 0;
    // return;

    // move out and prep
    chassis.moveDistance(-8, 1000, {.forwards = false});
    manualLiftState = 4;
    pros::delay(300);
    manualLiftState = 0;
    clawState  = 1;

    //MOVE MOVE MOVE
    chassis.turnToPoint(59.5, -14, 1000);
    chassis.moveToPoint(59.5, -14, 1000, {.maxSpeed = 60});
    chassis.swingToHeading(100, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 60});

    return;
}

void fourPinBack() { //OLD ONE
    chassis.setPose(1, -1, 180);
    chassis.distReset('L', 'F');

    toggleState = 1;
    pros::delay(1000);
    toggleState = 0;
    clawState = 3;
    chassis.moveDistance(-16, 1000, {.forwards = false});
    manualLiftState = 1;
    pros::delay(300);
    manualLiftState = 0;
    chassis.turnToHeading(90, 1000, {.maxSpeed = 80});
    chassis.moveDistance(22, 1000, {.maxSpeed = 50}, true);
    manualLiftState = 1;
    pros::delay(300);
    manualLiftState = 0;
    chassis.waitUntilDone();
    chassis.sendVoltage(2000, 250);
    manualLiftState = 4;
    pros::delay(650);
    clawState = 2;
    manualLiftState = 0;

    //approach first floor pin
    chassis.moveDistance(-18, 1000, {.forwards = false});
    chassis.distReset('F', 'R');
    manualLiftState = 4;
    pros::delay(400);
    manualLiftState = 0;
    chassis.turnToHeading(45, 1000, {.maxSpeed = 100});
    clawState = 1;
    chassis.moveToPoint(27, -19, 2000, {.maxSpeed = 30});
    manualLiftState = 1;
    pros::delay(300);
    manualLiftState = 0;
    pros::delay(300);

    //score first floor pin
    chassis.turnToHeading(180, 1000);
    chassis.distReset('L', 'F');
    manualLiftState = 1;
    pros::delay(550);
    manualLiftState = 0;
    chassis.moveDistance(25, 1000, {.maxSpeed = 50});
    chassis.sendVoltage(2000, 500);
    manualLiftState = 4;
    pros::delay(650);
    clawState = 2;
    manualLiftState = 0;

    //take second floor pin
    chassis.moveDistance(-20, 1000, {.forwards = false});
    chassis.distReset('L', 'F');
    chassis.turnToPoint(38, -46, 1000);
    manualLiftState = 4;
    pros::delay(500);
    clawState = 1;
    chassis.moveToPoint(38, -46, 4000, {.maxSpeed = 30});
    pros::delay(200);

    chassis.turnToHeading(-105, 1000);
    manualLiftState = 1;
    pros::delay(250);
    chassis.moveDistance(20, 1000, {.maxSpeed = 50});
    manualLiftState = 4;
    pros::delay(1500);
    clawState = 2;

    chassis.moveDistance(-15, 1000, {.forwards = false});
    chassis.turnToHeading(-45, 1000);
    chassis.moveDistance(60, 1000);
}

/*
void fourPinBack() { //TODO: NEW
    //L unreliable

    // reset
    
    chassis.setPose(100, -100, 180); //guarantees second quadrant reset

    // toggle
    clawState = 3; //begin low intake preload
    toggleState = 1;
    pros::delay(700); //TODO: good???
    toggleState = 0;

    // position preload
    chassis.moveDistance(-14.5, 1000, {.forwards = false}, true);
    manualLiftState = 1;
    pros::delay(500);
    manualLiftState = 0;
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1000, {.maxSpeed = 100});

    // move to score preload
    chassis.moveDistance(22, 1000, {.maxSpeed = 60});
    chassis.distReset('F', 'R');

    // score preload
    leftMotors.move(20);
    rightMotors.move(20);
    manualLiftState = 4;
    pros::delay(200);
    clawState = 2;
    manualLiftState = 0;
    pros::delay(500);
    leftMotors.move(0);
    rightMotors.move(0);

    // approach first floor pin
    chassis.moveDistance(-18, 1000, {.forwards = false}, true);
    manualLiftState = 4;
    pros::delay(200);
    manualLiftState = 0;
    chassis.waitUntilDone();

    // move for first stack
    chassis.turnToHeading(45, 1000);
    clawState = 1;
    chassis.moveDistance(20, 1000, {.minSpeed = 30}); //TODO: GOOD???
    chassis.moveDistance(14, 2000, {.maxSpeed = 20});
    
    // lift the lift a little bit
    manualLiftState = 1;
    pros::delay(300);
    manualLiftState = 0;

    // score first pin
    chassis.turnToHeading(190, 1000);
    chassis.distReset('L', 'F');
    chassis.moveDistance(25, 1000, {.maxSpeed = 60}, true);
    manualLiftState = 1;
    pros::delay(300); //TODO: TUNE THIS SHIT
    manualLiftState = 0;
    chassis.waitUntilDone();
    manualLiftState = 4;
    pros::delay(400);
    clawState = 2;
    manualLiftState = 0;
    pros::delay(200);

    //take second floor pin
    chassis.moveDistance(-20, 1000, {.forwards = false});
    clawState = 1;
    chassis.distReset('L', 'F');
    chassis.turnToPoint(38, -46, 1000);
    manualLiftState = 4;
    pros::delay(500);
    clawState = 1;
    chassis.moveToPoint(38, -46, 4000, {.earlyExitRange = 10});
    chassis.moveToPoint(38, -46, 4000, {.maxSpeed = 30});
    pros::delay(200);

    // score second floor pin
    chassis.turnToHeading(-105, 1000);
    manualLiftState = 1;
    pros::delay(250);
    chassis.moveDistance(20, 1000, {.maxSpeed = 80});
    manualLiftState = 4;
    pros::delay(1500);
    clawState = 2;
}
    */