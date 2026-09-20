#include "autonomous/autonomous.hpp"

void toggleTwoAuto() {
    leftMotors.move_voltage(-7000);
    rightMotors.move_voltage(-7000);

    pros::delay(400);

    leftMotors.move_voltage(7000);
    rightMotors.move_voltage(7000);

    pros::delay(800);

    leftMotors.move_voltage(-7000);
    rightMotors.move_voltage(-7000);

    pros::delay(400);

    leftMotors.move_voltage(7000);
    rightMotors.move_voltage(7000);
    
    pros::delay(800);

    leftMotors.move_voltage(-7000);
    rightMotors.move_voltage(-7000);

    pros::delay(400);
     
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}