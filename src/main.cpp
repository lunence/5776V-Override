// imports

// main.h
#include "main.h"

// autonomous
#include "autonomous/autonomous.hpp"
#include "autonomous/autonSelector.hpp"

// drivecode
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"

#include "drivecode/claw.hpp"
#include "drivecode/dr4b.hpp"
#include "drivecode/toggle.hpp"

// lemlib & pros
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/intersect.hpp"
#include "pros/motors.h"
#include "pros/misc.h"

#include <iostream>

void on_center_button() {

}

void initialize() {
	// reset the chassis position
	chassis.calibrate();
	chassis.setPose(0,0,0);

	// initialize the motors
	motorInit();

	// initialize the sensors
	sensorInit();
	liftTarget = 0;

	// initialize the tasks after hardware initialization
	taskInit();
	
	teamColor = 'R';

	// run autonSelector during the set up period
	// autonSelector();
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {
	// set the autonomous to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	// chassis.turnToHeading(90, 1000);
	// chassis.turnToHeading(180, 1000);
	// chassis.turnToHeading(0,1000);	
	
	// chassis.moveToPoint(0, 48, 1000);
	// chassis.moveToPoint(0, 12, 1000, {.forwards = false});
	// chassis.moveToPoint(0, 0, 1000, {.forwards = false});
	

	// manualControl = false;
	// // liftTarget = 45;
	// chassis.setPose(-1, -1, 90);
    // chassis.distReset('F', 'R');
	// //preloadAuto();
	
	fourPinRight();
	// wallPin();


	// chassis.setPose(-1, -1, 180);
    // chassis.distReset('R', 'F');

	// runAuton();
	
} 

void opcontrol() {
	// set the drive to coast
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	manualControl = true;
	
	// static bool antiTipping = false;

	//clawState = 0;
	//clawPiston.set_value(true);


	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		updateManualLift();
		// updatePidLift();
		updateClaw();
		// updateToggle();
		updateManualToggle();

		// angularPIDTuning(90);
		// linearPIDTuning(24);

		pros::delay(10);

	}
}