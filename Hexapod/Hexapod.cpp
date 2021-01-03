// Hexapod.cpp : This file contains the 'main' function. Program execution begins and ends there.

//#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Leg.h"
#include "ServoHandler.h"
#include "Position.h"
#include "Timer.h"

int main() {
    ServoHandler servo("COM3", 1.0, 1000000);

	//Positions of each coxa joint on the body
    Position frontLeftLegPos(91.925, 68.135, 32.0, 0.0, 0.0, 40.0/ 57.2957795);
	Position middleLeftLegPos(0.0, 111.0, 32.0, 0.0, 0.0, 90.0/ 57.2957795);
	Position rearLeftLegPos(-91.925, 68.135, 32.0, 0.0, 0.0, 130.0/ 57.2957795);
	Position frontRightLegPos(91.925, -68.135, 32.0, 0.0, 0.0, -40.0/ 57.2957795);
	Position middleRightLegPos(0.0, -111.0, 32.0, 0.0, 0.0, -90.0/ 57.2957795);
	Position rearRightLegPos(-91.925, -68.135, 32.0, 0.0, 0.0, -130.0/ 57.2957795);
	//Initial foot positions
	Position frontLeftFootPos;
	Position middleLeftFootPos;
	Position rearLeftFootPos;
	Position frontRightFootPos;
	Position middleRightFootPos;
	Position rearRightFootPos;

    Leg frontLeftLeg(1, 2, 3, frontLeftLegPos, frontLeftFootPos, servo);
	Leg middleLeftLeg(4, 5, 6, middleLeftLegPos, middleLeftFootPos, servo);
	Leg rearLeftLeg(7, 8, 9, rearLeftLegPos, rearLeftFootPos, servo);
	Leg frontRightLeg(16, 17, 18, frontRightLegPos, frontRightFootPos, servo);
	Leg middleRightLeg(13, 14, 15, middleRightLegPos, middleRightFootPos, servo);
	Leg rearRightLeg(10, 11, 12, rearRightLegPos, rearRightFootPos, servo);

	rearRightLeg.footPos.x = 1;

    for (uint8_t a = 1; a <= 18; a++) {
		servo.enableTorque(a, true);
    }
   /* frontLeftLeg.setFootPos(pos);
	middleLeftLeg.setFootPos(pos);
	rearLeftLeg.setFootPos(pos);
	frontRightLeg.setFootPos(pos);
	middleRightLeg.setFootPos(pos);
	rearRightLeg.setFootPos(pos);*/
	Position pos(320.0, -68.135, 0.0, 0.0, 0.0, 0.0);
	Position pos2(320.0, 68.135, 0.0, 0.0, 0.0, 0.0);
	Position pos3(0.0, 300.0, 0.0, 0.0, 0.0, 0.0);
	frontRightLeg.updateFootPos();
	frontLeftLeg.updateFootPos();
	middleLeftLeg.updateFootPos();

	Timer loopTimer;
	double fps = 40.0;// updates per second
	double timePerTick = 1000 / fps;
	double delta = 0;
	double now = loopTimer.getMillis();
	double lastTime = now;
	double timer = 0;
	int ticks = 0;
	long totalSeconds = 0;

	while (totalSeconds < 20) {
		now = loopTimer.getMillis();
		delta += (now - lastTime) / timePerTick;
		timer += now - lastTime;
		lastTime = now;

		if (delta >= 1) {
			//frontLeftLeg.setFootPos(pos);
			//middleLeftLeg.setFootPos(pos);
			//rearLeftLeg.setFootPos(pos);
			//frontRightLeg.setFootPos(pos);
			//middleRightLeg.setFootPos(pos);
			//rearRightLeg.setFootPos(pos);
			//pos.z -= 2;
			ticks++;
			delta--;
			//if (pos.z <= -122.0) {
			//	break;
			//}
		}

		if (timer >= 1000) {
			std::cout << "Updates per Second " << ticks << std::endl;
			timer = 0;
			ticks = 0;
			totalSeconds++;
		}



		
	}
	for (uint8_t a = 1; a <= 18; a++) {
		servo.enableTorque(a, false);
	}
	servo.closePort();
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
