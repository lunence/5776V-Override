#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>

void lemlib::Chassis::distanceReset(char xDirection, char yDirection) {
    //treat as lemlib motion so doesnt interfere with motions in progress
    // this->requestMotionStart();

    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* xDist = nullptr;
    DistResetSensors* yDist = nullptr;

    //if using front or back as x direction, need to rotate axes so x measures left and right
    if(xDirection == 'F') {
        xDist = &distSensors.front;
        rotated = M_PI_2;
    } else if(xDirection == 'B') {
        xDist = &distSensors.back;
        rotated = M_PI_2;
    } else if(xDirection == 'R') {
        xDist = &distSensors.right;
    } else if(xDirection == 'L') {
        xDist = &distSensors.left;
    }
        
    //if using left or right as y direction, need to rotate axes so y measures fwd and back
    if(yDirection == 'F') {
        yDist = &distSensors.front;
    } else if(yDirection == 'B') {
        yDist = &distSensors.back;
    } else if(yDirection == 'R') {
        yDist = &distSensors.right;
        rotated = M_PI_2;
    } else if(yDirection == 'L') {
        yDist = &distSensors.left;
        rotated = M_PI_2;
    }

    //invalidate sensors that return readings out of range
    if(xDist != nullptr && mmToIn(xDist->distance.get())>300) {
        xDist = nullptr;
    }

    if(yDist != nullptr && mmToIn(yDist->distance.get())>300) {
        yDist = nullptr;
    }

    //if both/essential distance sensors are bad, don't reset
    if(xDist == nullptr || yDist == nullptr) {
        this->endMotion();
        return;
    }

    //get current position
    lemlib::Pose currentPose = this->getPose(true);

    //this is going to be the reset pose with theta in degrees
    lemlib::Pose pose(0, 0, this->getPose(false).theta);

    
    // GETTING CORRECTED ANGLE: 

    //we need to reformat our heading into a reference angle to deal with simpler trig values
    //first, subtracting rotated re-zeros the reference to the wall direction so "straight-on" always reads as 0° going into trig
    //then we sanitize the given angle, ensuring our ref angle is in the first quadrant (makes trig simple)


    const float correctedAngle = lemlib::refAngle(true, 
        lemlib::sanitizeAngle(currentPose.theta-rotated, true));
    
    
    // DERIVING OFFSET MULTIPLIER: 

    //since our distance sensors are offset from the center, their distance will either be closer or farther to the wall
    // than the center, making our raw reading longer/shorter than what we need
    // if we take the sine of our heading - rotated (if applicable), we can tell this:
    // sin > 0 -> sensor swung toward wall -> ray too short -> subtract correction (-1)
    // sin < 0 -> sensor swung away from wall -> ray too long -> add correction    (+1)
    // we'll set this multiplier now and use it later
    

    const int offsetMultiplier = (std::sin(currentPose.theta-rotated) >= 0) ? -1 : 1;


    // ACTUAL DISTANCE CALCULATION
    // we need to use trig to reconstruct the perpendicular distance from the center of robot to the wall given our sensor's information

    // for this we need: 
    // - our centralRay = rawRay + tan(α) * offsetX * multiplier  (this is all lateral correction)
    // - - tan(α) = opp/adj, adj = offsetX, opp = difference in ray length
    // - - tan(α) * adj = opp = difference in length
    // - - we also add offsetY to account for that distance (vertical correction)

    // - to get perp distance, we take this centralRay and our heading
    // - - centralRay = hypotenuse, perpDistance = adj
    // - - cos(α) = adj/hypotenuse, cos(α) * hypotenuse = adj; cos(α) * centralRay = perpDistance
    


    //x perpDistance 
    float xRawRay = mmToIn(xDist->distance.get());
    float xLatCorr = tan(correctedAngle) * xDist->offsetX * offsetMultiplier;
    float xVertCorr = xDist ->offsetY;
    float xPerpDistance = 0;
    
    if(xDist != nullptr){
        xPerpDistance = cos(correctedAngle) * (xRawRay + xLatCorr + xVertCorr);
    }


    //y perpDistance 
    float yRawRay = mmToIn(yDist->distance.get());
    float yLatCorr = tan(correctedAngle) * yDist->offsetY * offsetMultiplier;
    float yVertCorr = yDist ->offsetY;
    float yPerpDistance = 0;

    if(yDist != nullptr){
        yPerpDistance = cos(correctedAngle) * (yRawRay + yLatCorr + yVertCorr);
    }
   
   

    // FINAL RESETS:
        //x reset
    if(currentPose.x > 0){ // if on east half of coord plane, +x coord for pose
        pose.x = lemlib::halfWidth - xPerpDistance;
    } else if(currentPose.x < 0) { //else, -x coord, so subtract width from perpdistance
        pose.x = xPerpDistance - lemlib::halfWidth;
    }

    //y reset
    if(currentPose.y > 0){ //if on north half of coord plane, +y coord for pose
        pose.y = lemlib::halfWidth - yPerpDistance;
    } else if(currentPose.y < 0){ //else, -y coord, so subtract width from perpdistance
        pose.y = yPerpDistance - lemlib::halfWidth;
    }

    this->setPose(pose);
    this->endMotion();
    return;
}