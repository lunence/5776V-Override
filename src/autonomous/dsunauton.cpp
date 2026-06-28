#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void dsunauto() {
    // beginning turn
    // intakeState = 1;

    chassis.setPose(1, -1, 0);
    chassis.distanceReset('F', 'L');

    chassis.moveToPoint(0, -67, 1000);
    chassis.moveToPoint(0, -72, 1000);
}