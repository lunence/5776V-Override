#include "autonomous/autonomous.hpp"



void fourPinRight() {
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

    return;

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