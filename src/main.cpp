// imports

// main.h
#include "main.h"

// autonomous
#include "autonomous/autonomous.hpp"
#include "autonomous/autonSelector.hpp"

// drivecode
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/chainbar.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/toggle.hpp"

// lemlib & pros
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/intersect.hpp"
#include "pros/motors.h"
#include "pros/misc.h"

// sdcard
// #include "sdcard/sdtest.hpp"
// #include "sdcard/sdmain.hpp"

// // anti tip and all bs stuff
// static constexpr float IMU_PITCH_SIGN = -1.0; // flip the sign of the pitch if the bot is flipped, shudnt be changed

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

	// initialize the tasks after hardware initialization
	taskInit();
	

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

	// runAuton();
	drc();
} 

void opcontrol() {
	// set the drive to coast
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	autoCascade = false;
	// static bool antiTipping = false;

	//clawState = 0;
	//clawPiston.set_value(true);


	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		updateCascadeManual();
		updateChainBar();
		updateManualClaw();

		pros::delay(10);

		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		// 	cascadeTarget += 10;
		// 	pros::delay(200);
		// }

		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		// 	cascadeTarget -= 10;
		// 	pros::delay(200);
		// }

		/*
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			chainBar.move_voltage(12000);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			chainBar.move_voltage(-12000);
		} else chainBar.move_voltage(0);
		 */
		

		/*

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		
		*/


	}
}