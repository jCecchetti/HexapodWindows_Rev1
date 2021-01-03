#pragma once

#ifndef LEG_H_
#define LEG_H_
#include "ServoHandler.h"
#include "Position.h"

class Position;

class Leg
{
public:
	Leg();
	Leg(int, int, int, Position, Position, ServoHandler&);
	bool updateFootPos();
	virtual ~Leg();
	Position footPos;

private:
	ServoHandler servo;
	int coxaID;
	int femurID;
	int tibiaID;
	bool calculateAngles(double, double, double);
	void setServoAngle(int, double);
	//AdafruitServo servo1, servo2, servo3;

	double pi = 3.141592;

	//All angles in radians
	double coxaAngle = 0.0;
	double femurAngle = 0.0;
	double tibiaAngle = 0.0;
	float coxaCenter = 0.0f;
	float femurCenter = 0.0f;
	float tibiaCenter = 12.0 / 180.0 * pi;

	//Length of leg parts in mm
	double COXA = 45.0;
	double FEMUR = 104.0;
	double TIBIA = 160.0;

	const Position localBasePos;
};

#endif /* LEG_H_ */