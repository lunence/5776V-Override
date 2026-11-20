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
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	manualControl = false;

	// auton functions!
	skills();
} 

void opcontrol() {
	// set the drive to coast
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE); //TODO: reconsider this
	manualControl = true;

	bool l1Pressed = false;
	bool l2Pressed = false;
	bool r1Pressed = false;
	bool r2Pressed = false;

	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		updateManualLift();
		updateManualToggle();
		updateClaw();

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) liftRot.set_position(0);

		pros::delay(10);

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		// 	if (!l1Pressed) target += 20;
		// 	l1Pressed  = true;
		// } else l1Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		// 	if (!l2Pressed) target -= 20;
		// 	l2Pressed  = true;
		// } else l2Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		// 	if (!r1Pressed) target += 50;
		// 	r1Pressed  = true;
		// } else r1Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		// 	if (!r2Pressed) target -= 50;
		// 	r2Pressed  = true;
		// } else r2Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		// 	chassis.setPose(0, 0, 0);
		// 	chassis.moveToPoint(0, 12, 2000);
		// } else l1Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		// 	chassis.setPose(0, 0, 0);
		// 	chassis.moveToPoint(0, 24, 2000);
		// } else l2Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		// 	chassis.setPose(0, 0, 0);
		// 	chassis.moveToPoint(0, 36, 2000);
		// } else r1Pressed = false;

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		// 	chassis.setPose(0, 0, 0);
		// 	chassis.moveToPoint(0, 48, 2000);
		// } else r2Pressed = false;
	}
}