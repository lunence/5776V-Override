// #include <cmath>
// #include "lemlib/chassis/chassis.hpp"

// void lemlib::chassis::gomax(int voltage) {
//     this->move_voltage(voltage);

//     pros::delay(100);
//     // start running motor at provided voltage
//     while (true) {
//         // loop constantly checking if velocity is extremely low
//         // this happens when the motor is stalling so we need to stop sending voltage
//         if (std::abs(this->get_actual_velocity()) <= 50) {
//             break;
//         }
//         pros::delay(20);

//     }

//     this->move_voltage(0);


// }