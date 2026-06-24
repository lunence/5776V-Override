#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "objects.hpp"
#include "drivecode/util.hpp"
#include "pros/distance.hpp"

//drive motors
//TODO: make odom compatible with 5.5w 11w mixed
pros::MotorGroup leftMotors({0, 0, 0}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({0, 0, 0}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(0);
pros::Rotation horizRotation(0);
pros::Distance distRight(0);
pros::Distance distLeft(0);
pros::Distance distFront(0);
pros::Distance distBack(0);

//odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,
    0
);

//odom sensors
lemlib::OdomSensors odomSensorsDrive(
    nullptr,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);


//drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    11.44,
    3.25,
    450,
    60 //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

//controller settings
lemlib::ControllerSettings lateralController(
    10,                           //kP
    0.16,                         //kI
    56,                           //kD    
    4,                   //windup range
    0.5,                    //small error
    50,           //small error timeout
    0,                    //large error 
    500,           //large error timeout
    0                           //slew
);

lemlib::ControllerSettings angularController(
    2.75,
    0.32,
    20,
    5,
    2,
    50,
    0,
    500,
    0
);

//distance sensors
lemlib::DistanceSensors distSensors(distFront, 0, 0,
                                    distBack, 0, 0,
                                    distLeft, 0, 0,
                                    distRight, 0, 0);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive,
    distSensors
);
