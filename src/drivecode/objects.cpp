#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"

// TODO: CONTROLS
// Buttons on the controller that control assigned subsystems
pros::controller_digital_e_t cbUpControl = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t cbDownControl = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t cascadeUpControl = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t cascadeDownControl = pros::E_CONTROLLER_DIGITAL_L2;
pros::controller_digital_e_t cascadeManualControl = pros::E_CONTROLLER_DIGITAL_LEFT;
pros::controller_digital_e_t clawControl = pros::E_CONTROLLER_DIGITAL_Y;
pros::controller_digital_e_t clawOpenControl = pros::E_CONTROLLER_DIGITAL_B;

// pros::controller_digital_e_t toggleControl = pros::E_CONTROLLER_DIGITAL_DOWN;

// TODO: Add actual drivetrain motor ports
pros::MotorGroup leftMotors({13, -14}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({12, -11}, pros::MotorGearset::blue);

// TODO: Add actual intake motor ports
pros::Motor clawRoller(7, pros::MotorGearset::green);

// TODO: Add actual cascade ports and rotation
// cascade and chainbar motors
pros::MotorGroup cascadeFulls({-2, 3}, pros::MotorGearset::green);//all motors for cascade are green
pros::Motor cascadeHalf(1, pros::MotorGearset::green); // 5.5 w
pros::Motor chainBar (20, pros::MotorGearset::green);//chain bar has a green motor

// TODO: Add actual cascade sensor ports
// cascade distance sensor for macro
pros::Distance distCascade(19);

// chain bar/cascade rotation sensors
pros::Rotation chainBarRotation(18);
pros::Rotation cascadeRotation(16);

// TODO: Add actual claw ports
// pistons
pros::adi::DigitalOut clawPiston('H');

// TODO: Add actual distance sensor ports
// distance sensors for dsr
pros::Distance distFront(17);
pros::Distance distBack(6);
pros::Distance distLeft(9);
pros::Distance distRight(4);

// TODO: Add actual odometry ports
// odometry sensors for chassis
pros::Rotation horizRotation(16);
pros::Imu imu(15);

// odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2.75,
    0
);

// odom sensors
lemlib::OdomSensors odomSensorsDrive(
    nullptr,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);

//TODO: ADD ACTUAL VALUES
// drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    10.445,
    2.75,
    450,
    99999 //we have tractions!
    //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

// lateral pid controller
lemlib::ControllerSettings lateralController(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular pid controller
lemlib::ControllerSettings angularController(6, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// distance sensors
lemlib::DistanceSensors distSensors(distFront, -4.13, 5.27,
                                    distBack, 2.99, 4.66,
                                    distLeft, 2.04, 4.80,
                                    distRight, -3.18, 4.80);

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

// chain bar pid
lemlib::PID chainBarPID(2,
                         // proportional gain (kP)
                         0.3,
                         // integral gain (kI)
                         20,
                         // derivative gain (kD)
                         5,
                         // antiwindup
                         true
                         // sign flip reset boolean
);

// cascade pid
lemlib::PID cascadePID(15,
                         // proportional gain (kP)
                         0.0,
                         // integral gain (kI)
                         2,
                         // derivative gain (kD)
                         5,
                         // antiwindup
                         true
                         // sign flip reset boolean
);