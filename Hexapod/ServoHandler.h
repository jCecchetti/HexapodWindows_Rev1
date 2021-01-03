#pragma once
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamixel_sdk.h"     // Uses Dynamixel SDK library

// Control table address
#define ADDR_MX_TORQUE_ENABLE           24                  // Control table address is different in Dynamixel model
#define ADDR_MX_GOAL_POSITION           30
#define ADDR_MX_PRESENT_POSITION        36

// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MOVING_STATUS_THRESHOLD     10                  // Dynamixel moving status threshold


class ServoHandler {
public:
	ServoHandler();
	ServoHandler(const char* deviceName, float protocolVerson, int baudrate);
	void closePort();
	void enableTorque(uint8_t, bool);
	void setGoalAngle(uint8_t, double);
	double getPresentAngle(uint8_t);

private:
	
	dynamixel::PortHandler* portHandler;
	dynamixel::PacketHandler* packetHandler;
	int dxl_comm_result = COMM_TX_FAIL;
	int dxl_goal_position = 500;						// Goal position
	uint8_t dxl_error = 0;                          // Dynamixel error
	uint16_t dxl_present_position = 0;              // Present position
};

