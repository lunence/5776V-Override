#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"

pros::controller_digital_e_t clawOpen = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t clawSpin = pros::E_CONTROLLER_DIGITAL_R2; 

pros::controller_digital_e_t liftUp = pros::E_CONTROLLER_DIGITAL_L1; //manual control buttons
pros::controller_digital_e_t liftDown = pros::E_CONTROLLER_DIGITAL_L2;

pros::controller_digital_e_t toggleButton = pros::E_CONTROLLER_DIGITAL_Y;

// pros::controller_digital_e_t CONTROL5 = pros::E_CONTROLLER_DIGITAL_LEFT;
// pros::controller_digital_e_t CONTROL6 = pros::E_CONTROLLER_DIGITAL_DOWN; //pid dr4b down
pros::controller_digital_e_t overrideButton = pros::E_CONTROLLER_DIGITAL_DOWN; 

//TODO: ALL READINGS WILL BE SKEWED BY 5.5s SO DON'T USE THEM
pros::MotorGroup leftMotors({12, -13, -14}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-20, 16, 15}, pros::MotorGearset::blue);

// 1 half motor on claw
pros::Motor claw(7, pros::MotorGearset::green);

// 2 red motors on dr4b
pros::MotorGroup lift({-3, 1}, pros::MotorGearset::green);

// toggle roller motor
pros::Motor toggle(2, pros::MotorGearset::green);

// lift rot, toggle colors
pros::Rotation liftRot(-8);
pros::adi::Button liftLimit(0);
pros::Optical toggleOptical(0);

// 4 distance sensors for dsr
pros::Distance distFront(21);
pros::Distance distBack(10);
pros::Distance distLeft(11);
pros::Distance distRight(6);

// odometry sensors
pros::Rotation horizRotation(9);
pros::Rotation vertRotation(0);
pros::Imu imu(17);

// odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2.75,
    0
);

lemlib::TrackingWheel vertOdom(
    &vertRotation, 
    2,
    0
);

// odom sensors
lemlib::OdomSensors odomSensorsDrive(
    &vertOdom,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);

// drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    11.4,
    2.75,
    450,
    99999 // we have tractions!
    //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

// lateral pid controller
lemlib::ControllerSettings lateralController(0, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular pid controller
lemlib::ControllerSettings angularController(4, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              20, // derivative gain (kD)
                                              5, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// distance sensors
lemlib::DistanceSensors distSensors(distFront, 4.054, 4.663,
                                    distBack, 5.954, 5.226,
                                    distLeft, -3.454, 5.176,
                                    distRight, -3.454, 5.176);

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive,
    distSensors
);

// double reverse four bar
lemlib::PID liftPID(20,
                    // proportional gain (kP)
                    0.0,
                    // integral gain (kI)
                    7.5,
                    // derivative gain (kD)
                    5,
                    // antiwindup
                    true
                    // sign flip reset boolean
);