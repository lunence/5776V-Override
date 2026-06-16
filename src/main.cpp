#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "lemlib/intersect.hpp"
#include "autonomous/autonSelector.hpp"
#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"

void on_center_button() {}

void initialize() {
	chassis.calibrate();
	chassis.setPose(0,0,0);

	taskInit();
	motorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	sdWriter::activeFile = "test.csv";
	// Register a simple timestamp getter so the writer has at least one column
	sdWriter::setData("test.csv", {
		[]() { return std::to_string(pros::millis()); },
	});
	sdTest::run();
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	pros::screen::print(pros::E_TEXT_MEDIUM, 7, "upload successful");

	while (true) {
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		//delay
		pros::delay(10);
	}
}