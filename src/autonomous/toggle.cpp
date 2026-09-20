#include "autonomous/autonomous.hpp"

void toggleOneAuto() {
    leftMotors.move_voltage(-5000);
    rightMotors.move_voltage(-5000);

    pros::delay(200);

    leftMotors.move_voltage(5000);
    rightMotors.move_voltage(5000);

    pros::delay(300);
     
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}

void toggleTwoAuto() {
    leftMotors.move_voltage(-5000);
    rightMotors.move_voltage(-5000);

    pros::delay(200);

    leftMotors.move_voltage(5000);
    rightMotors.move_voltage(5000);

    pros::delay(300);

    leftMotors.move_voltage(-5000);
    rightMotors.move_voltage(-5000);

    pros::delay(200);

    leftMotors.move_voltage(5000);
    rightMotors.move_voltage(5000);
    
    pros::delay(300);
     
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}