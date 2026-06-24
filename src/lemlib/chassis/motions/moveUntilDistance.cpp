#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"

//TODO: test
void lemlib::Chassis::moveUntilDistance(char dir, float exitDist, float x, float y, float timeout, MoveToPointParams params) {
    //start movement async
    this->moveToPoint(x, y, timeout, params, true); 

    //pick active dist sensor for side
    DistResetSensors* distSensor = nullptr;
    if(dir == 'F') {
        distSensor = &distSensors.front;
    } else if(dir == 'B') {
        distSensor = &distSensors.back;
    }

    //delay until distance sensor detects exitDist inches or motion is complete
    while(mmToIn(distSensor->distance.get()) > exitDist && this->isInMotion()) {
        pros::delay(10);
    }

    this->endMotion(); //TODO: test if this works
    this->drivetrain.leftMotors->move_velocity(0);
    this->drivetrain.rightMotors->move_velocity(0);
}