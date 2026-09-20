#include "autonomous/autonomous.hpp"

void toggleOneAuto() {
    leftMotors.move_voltage(-5000);
    rightMotors.move_voltage(-5000);

    pros::delay(400);

    leftMotors.move_voltage(5000);
    rightMotors.move_voltage(5000);

    pros::delay(800);
     
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}

void toggleTwoAuto() {
    leftMotors.move_voltage(-5000);
    rightMotors.move_voltage(-5000);

    pros::delay(400);

    leftMotors.move_voltage(5000);
    rightMotors.move_voltage(5000);

    pros::delay(800);

    leftMotors.move_voltage(-5000);
    rightMotors.move_voltage(-5000);

    pros::delay(400);

    leftMotors.move_voltage(5000);
    rightMotors.move_voltage(5000);
    
    pros::delay(800);
     
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}