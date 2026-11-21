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

pros::controller_digital_e_t overrideButton = pros::E_CONTROLLER_DIGITAL_DOWN; 
//additional binds: A=zero lift

//TODO: ALL READINGS WILL BE SKEWED BY 5.5s SO DON'T USE THEM
pros::MotorGroup leftMotors({-11, -15, 13}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({20, -18, 19}, pros::MotorGearset::blue);

// 1 half motor on claw
pros::Motor claw(4, pros::MotorGearset::green);

// 2 red motors on dr4b
pros::MotorGroup lift({-5, 1}, pros::MotorGearset::green);

// toggle roller motor
pros::Motor toggle(14, pros::MotorGearset::green);

// lift rot, toggle colors
pros::Rotation liftRot(-6);
pros::adi::Button liftLimit(0); //TODO: not added
pros::Optical toggleOptical(0); //TODO: not added

// 4 distance sensors for dsr
pros::Distance distFront(7);
pros::Distance distBack(12);
pros::Distance distLeft(2);
pros::Distance distRight(10);

// odometry sensors
pros::Rotation horizRotation(-17);
pros::Rotation vertRotation(-16);
pros::Imu imu(21);

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
//TODO: tune error ranges + windup
lemlib::ControllerSettings lateralController(6, // proportional gain (kP)
                                              0.2, // integral gain (kI)
                                              15, // derivative gain (kD)
                                              3, // anti windup
                                              0.5, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular pid controller
lemlib::ControllerSettings angularController(2.5, // proportional gain (kP)
                                              0.08, // integral gain (kI)
                                              20, // derivative gain (kD)
                                              6, // anti windup
                                              2, // small error range, in deg
                                              100, // small error range timeout, in milliseconds
                                              0, // large error range, in deg
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// distance sensors
lemlib::DistanceSensors distSensors(distFront, 4.507, 4.663,
                                    distBack, -5.44, 5.226, 
                                    distLeft, -3, 5.176, //prev -3.454
                                    distRight, 3, 5.176);

                                    //TODO: left and right will be biased off bc towers bent outward on purpose

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
lemlib::PID liftPID(5.8,
                    // proportional gain (kP)
                    0.2,
                    // integral gain (kI)
                    0,
                    // derivative gain (kD)
                    6,
                    // antiwindup
                    true
                    // sign flip reset boolean
);