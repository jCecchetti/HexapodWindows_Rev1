#pragma once

#ifndef SERVO_H_
#define SERVO_H_

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamixel_sdk.h"     // Uses Dynamixel SDK library
#include <iostream>

namespace Servo {
    // Control table address
    #define ADDR_MX_TORQUE_ENABLE           24                  // Control table address is different in Dynamixel model
    #define ADDR_MX_GOAL_POSITION           30
    #define ADDR_MX_PRESENT_POSITION        36

    #define DEVICENAME                      "COM3"              // Check which port is being used on your controller
                                                                // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

    #define TORQUE_ENABLE                   1                   // Value for enabling the torque
    #define TORQUE_DISABLE                  0                   // Value for disabling the torque
    #define DXL_MINIMUM_POSITION_VALUE      500                 // Dynamixel will rotate between this value
    #define DXL_MAXIMUM_POSITION_VALUE      600                 // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
    #define DXL_MOVING_STATUS_THRESHOLD     10                  // Dynamixel moving status threshold

    dynamixel::PortHandler* portHandler;
    dynamixel::PacketHandler* packetHandler;
    int dxl_comm_result = COMM_TX_FAIL;
    int dxl_goal_position = 500;						// Goal position
    uint8_t dxl_error = 0;                          // Dynamixel error
    uint16_t dxl_present_position = 0;              // Present position

	int presentPosition[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int goalPosition[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	inline void openPort(const char *deviceName, float protocolVerson, int baudrate) {
        std::cout << "motor\n";
        // Initialize PortHandler instance
        // Set the port path
        // Get methods and members of PortHandlerLinux or PortHandlerWindows
        portHandler = dynamixel::PortHandler::getPortHandler(deviceName);

        // Initialize PacketHandler instance
        // Set the protocol version
        // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
        packetHandler = dynamixel::PacketHandler::getPacketHandler(protocolVerson);
        // Open port
        if (portHandler->openPort()) {
            printf("Succeeded to open the port!\n");
        }
        else {
            printf("Failed to open the port!\n");
        }

        // Set port baudrate
        if (portHandler->setBaudRate(baudrate)) {
            printf("Succeeded to change the baudrate!\n");
        }
        else {
            printf("Failed to change the baudrate!\n");
        }
    }

    inline void closePort() {
        // Close port
        portHandler->closePort();
    }

    inline void enableTorque(uint8_t id, bool enable) {
        if (enable) {
            // Enable Dynamixel Torque
            dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, id, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
            if (dxl_comm_result != COMM_SUCCESS) {
                printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
            }
            else if (dxl_error != 0) {
                printf("%s\n", packetHandler->getRxPacketError(dxl_error));
            }
            else {
                printf("Dynamixel has been successfully connected \n");
            }
        }
        else {
            // Disable Dynamixel Torque
            dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, id, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
            if (dxl_comm_result != COMM_SUCCESS)
            {
                printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
            }
            else if (dxl_error != 0)
            {
                printf("%s\n", packetHandler->getRxPacketError(dxl_error));
            }
        }
    }

    inline void setGoalAngle(uint8_t id, double angle) {
        goalPosition[id] = angle;
        // Write goal position
        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, id, ADDR_MX_GOAL_POSITION, dxl_goal_position, &dxl_error);
        if (dxl_comm_result != COMM_SUCCESS) {
            printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
        }
        else if (dxl_error != 0) {
            printf("%s\n", packetHandler->getRxPacketError(dxl_error));
        }
    }

    inline double getPresentAngle(uint8_t id)
    {
        // Read present position
        dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, id, ADDR_MX_PRESENT_POSITION, &dxl_present_position, &dxl_error);
        if (dxl_comm_result != COMM_SUCCESS) {
            printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
        }
        else if (dxl_error != 0) {
            printf("%s\n", packetHandler->getRxPacketError(dxl_error));
        }

        printf("[ID:%03d]  PresPos:%03d\n", 3, dxl_present_position);
        return 0.0;
    }
}

#endif /* SERVO_H_ */