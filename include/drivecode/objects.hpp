#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/optical.hpp"

extern pros::Motor cascade;
extern pros::Motor scoreMech;

//drive motor declarations
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//sensor declarations
extern pros::Imu imu;
extern pros::Optical color;
extern pros::Rotation horizRotation;
extern pros::Distance distRight;
extern pros::Distance distLeft;
extern pros::Distance distFrontLeft;
extern pros::Distance distFrontRight;
extern pros::Distance distBack;
extern pros::Distance distCascade;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
