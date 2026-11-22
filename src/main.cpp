// imports
#include "main.h"
#include "autonomous/autonomous.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/dr4b.hpp"
#include "drivecode/toggle.hpp"
#include "pros/misc.h"

void on_center_button() {}

void initialize() {
	// reset the chassis position
	chassis.calibrate();
	chassis.setPose(0,0,0);
	claw.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	sensorInit();
	taskInit();
	
	teamColor = 'R';
}

void disabled() {}
void competition_initialize() {}

void autonomous() {
	// auton motor modes
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	manualControl = false;
	overrideMotionLimits = false;
	autoToggle = false;

	// auton functions!
	skills();
	// fourPinBack();
	// preloadRight();
} 

void opcontrol() {
	// set the drive to coast
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	manualControl = true;
	overrideMotionLimits = false;
	autoToggle = false;

	// lemlib::ExpoDriveCurve angularDriveCurve(2, 0, 1.025);


	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		updateManualLift();
		updateManualToggle();
		updateClaw();

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) liftRot.set_position(0);

		pros::delay(10);
	}
}