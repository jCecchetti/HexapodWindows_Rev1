#include "Leg.h"
#include <math.h>
#include "Position.h"
#include <iostream>
//#include "Servo.h"
#include <stdio.h>
#include "ServoHandler.h"

Leg::Leg() {//TODO
	ServoHandler servo1 = ServoHandler();
	servo = servo1;
	

}
Leg::Leg(int coxaID, int femurID, int tibiaID, Position localBasePos, Position footPos, ServoHandler& servo) : 
	coxaID(coxaID), femurID(femurID), tibiaID(tibiaID), localBasePos(localBasePos), footPos(footPos), servo(servo){
}

bool Leg::updateFootPos() {
	calculateAngles(footPos.x, footPos.y, footPos.z);
	//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	servo.setGoalAngle(coxaID, -coxaAngle * 57.2957795);
	servo.setGoalAngle(femurID, femurAngle * 57.2957795 - 90.0);
	servo.setGoalAngle(tibiaID, -tibiaAngle * 57.2957795 + 90.0 + 12.0);
	return true;
}

bool Leg::calculateAngles(double local_x, double local_y, double local_z) {
	//transform local coordinates to make the coxa joint the origin
	double x = (local_x - localBasePos.x) * cos(-localBasePos.yaw) - (local_y - localBasePos.y) * sin(-localBasePos.yaw);
	double y = (local_x - localBasePos.x) * sin(-localBasePos.yaw) + (local_y - localBasePos.y) * cos(-localBasePos.yaw);
	double z = local_z - localBasePos.z;
	//std::cout << x << " " << y << " " << z << std::endl;
	//Calculate required angles using inverse kinematics
	coxaAngle = atan2(y, x);
	double hyp = sqrt(z*z + pow((sqrt(x*x + y*y) - COXA),2));
	femurAngle = acos(-z / hyp) + acos((-TIBIA * TIBIA + FEMUR * FEMUR + hyp * hyp) / (2 * FEMUR * hyp));
	tibiaAngle = acos((-hyp * hyp + TIBIA * TIBIA + FEMUR * FEMUR) / (2 * TIBIA * FEMUR));
	std::cout << coxaAngle* 57.2957795 << std::endl;
	std::cout << femurAngle* 57.2957795 << std::endl;
	std::cout << tibiaAngle* 57.2957795 << std::endl;
	//std::cout << acos(-z / hyp) * 57.2957795 << std::endl;
	/*std::cout << hyp << std::endl;*/
	return true;
}

void Leg::setServoAngle(int channel, double angle) {
	
}

Leg::~Leg() {
	// TODO Auto-generated destructor stub
}
