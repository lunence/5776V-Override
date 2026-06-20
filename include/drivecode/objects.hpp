#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/optical.hpp"

//piston declarations
// extern pros::adi::DigitalOut scraper;
// extern pros::adi::DigitalOut wing;
// extern pros::adi::DigitalOut trapdoor;
// extern pros::adi::DigitalOut intakeLift;
// extern pros::adi::DigitalOut midDescore;

//intake motor declarations
// extern pros::Motor topIntake;
// extern pros::Motor midIntake;
// extern pros::Motor bottomIntake;

//drive motor declarations
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//sensor declarations
// extern pros::Imu imu;
// extern pros::Optical color;
// extern pros::Rotation horizRotation;
extern pros::Distance distRight;
extern pros::Distance distLeft;
extern pros::Distance distFront;
extern pros::Distance distBack;
extern pros::Vision visionFront;
extern pros::Vision visionBack;

// color signature declarations
extern pros::vision_signature_s_t signatureBluePin;
extern pros::vision_signature_s_t signatureYellowPin;
extern pros::vision_signature_s_t signatureRedPin;

// color code declarations
extern pros::vision_color_code_t codeBLUEYELLOW_F;
extern pros::vision_color_code_t codeREDYELLOW_F;
extern pros::vision_color_code_t codeBLUERED_F;
extern pros::vision_color_code_t codeBLUEYELLOW_B;
extern pros::vision_color_code_t codeREDYELLOW_B;
extern pros::vision_color_code_t codeBLUERED_B;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
