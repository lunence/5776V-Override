#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

//motor declarations
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//sensor declarations
extern pros::Imu imu;
extern pros::Rotation horizRotation;
extern pros::Distance distRight;
extern pros::Distance distLeft;
extern pros::Distance distFront;
extern pros::Distance distBack;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
