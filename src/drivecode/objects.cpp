#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "objects.hpp"
#include "drivecode/util.hpp"
#include "pros/distance.hpp"
#include "pros/rotation.hpp"

pros::Motor cascade(11, pros::MotorGearset::blue);

pros::Distance distCascade(1);

pros::Distance distFrontLeft(0);
pros::Distance distFrontRight(0);
pros::Distance distBack(0);
pros::Distance distLeft(0);
pros::Distance distRight(0);

pros::MotorGroup leftMotors({0, 0, 0});
pros::MotorGroup rightMotors({0, 0, 0});

pros::Rotation horizRotation(0);
pros::Imu imu(0);

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
    0,                         //kI
    56,                           //kD
    4,                   //windup range
    0.5,                    //small error
    50,           //small error timeout
    0,                    //large error 
    500,           //large error timeout
    0                           //slew
);

lemlib::ControllerSettings angularController(
    2.73, //TODO: BOOSTED THIS BY 0.25
    0,
    18,
    5,
    2,
    50,
    0,
    500,
    0
);

//distance sensors
lemlib::DistanceSensors distSensors(distFrontLeft, -4.13, 5.27,
                                    distFrontRight, 4.13, 5.27,
                                    distBack, 2.99, 4.66,
                                    distLeft, 2.04, 4.80,
                                    distRight, -3.18, 4.80);

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
