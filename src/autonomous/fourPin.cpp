#include "autonomous/autonomous.hpp"
#include "autonomous/autonMacros.hpp"

void fourPinLeft() {
        pros::screen::print(pros::E_TEXT_SMALL, 10, "four pin left");


}
        
void fourPinRight() {
        pros::screen::print(pros::E_TEXT_SMALL, 10, "four pin right");
        
        // reset and then toggles
        chassis.setPose(1, -1, 180);
        chassis.distReset('F', 'L');
        // flip pin twice
        toggleMacro(2, 5);

        //curve to alliance
        chassis.moveToPose(22, -48, -90, 1000, {.forwards = false});
        
        chassis.turnToPoint(24, -68, 500);
        chassis.moveToPoint(24, -68, 1000);

        // grab pin return to goal and score
        chassis.moveToPoint(24, -48, 0, {.forwards = false});

        
        // chain bar and cascade
        scoreMacro(0);
        
        //turn to next pins
        chassis.turnWithPower(180, 10, 1000, {}, false);
        chassis.moveToPoint(24, -58, 1000);
        
        //score
        chassis.moveToPoint(24, -50, 1000, {.forwards = false});
        scoreMacro(1);
        
        //next pin
        chassis.turnWithPower(90, 10, 1000, {}, false);
        chassis.moveToPoint(48, -48, 1000);

        //score
        chassis.moveToPoint(-26, -48, 1000);
        scoreMacro(2);


}

      