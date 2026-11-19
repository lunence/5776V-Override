#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"

void lemlib::Chassis::sendVoltage(float leftPower, float rightPower, int time, bool async) {
    this->requestMotionStart();
    if(!this->motionRunning) return;

    if (async) {
        pros::Task task([&]() { sendVoltage(leftPower, rightPower, time, async); });
        this->endMotion();
        pros::delay(10); // delay to give the task time to start
        return;
    }
    
    Timer timer(time);

    while(!timer.isDone()) {
        this->drivetrain.leftMotors->move(leftPower);
        this->drivetrain.rightMotors->move(rightPower);

        pros::delay(10);
    }

    this->drivetrain.leftMotors->move(0);
    this->drivetrain.rightMotors->move(0);

    this->endMotion();
}