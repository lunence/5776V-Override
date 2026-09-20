#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/chainbar.hpp"
#include "drivecode/cascade.hpp"

void scoreMacro(int scoreLevel) {
    // bring cascade to the correct score height
    cascadeTarget = scoreHeights[scoreLevel];
    // load chainbar to position
    chainBarState = 3;
    // claw open
    clawState = 2;
    // bring cascade up a bit to not hit the stack
    cascadeTarget = scoreHeights[scoreLevel] + 5;
    // chainbar back to neutral
    chainBarState = 1;
    // // cascade back down
    //cascadeTarget = scoreHeights[0]
}

void toggleMacro(int flips, int distance) {
    for (int i = 0; i < flips; i++) {
        chassis.moveDistance(distance, 300);
        chassis.moveDistance(-distance, 300);
    }
}

void loadingMacro() {
    cascadeTarget = scoreHeights[0];
    chainBarState = 1;
    clawState = 1;
}
