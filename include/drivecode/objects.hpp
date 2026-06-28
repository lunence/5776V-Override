#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/optical.hpp"

// drive motors
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// intake
extern pros::Motor intake; // 5.5w

// cascade and chainbar motors
extern pros::Motor cascadeL;
extern pros::Motor cascadeR;
extern pros::Motor chainBar;

// cascade distance sensor for macro
extern pros::Distance distCascade;

// piston claw
extern pros::adi::DigitalOut pistonClawRotate;
extern pros::adi::DigitalOut pistonClawClose;

// distance sensors for dsr
extern pros::Distance distFrontLeft;
extern pros::Distance distFrontRight;
extern pros::Distance distBack;
extern pros::Distance distLeft;
extern pros::Distance distRight;

// odometry sensors for chassis
extern pros::Rotation horizRotation;
extern pros::Imu imu;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
