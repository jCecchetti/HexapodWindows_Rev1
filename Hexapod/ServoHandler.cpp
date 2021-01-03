#include "ServoHandler.h"
#include <iostream>

ServoHandler::ServoHandler() {

}
ServoHandler::ServoHandler(const char* deviceName, float protocolVerson, int baudrate) {
    // Initialize PortHandler instance
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    portHandler = dynamixel::PortHandler::getPortHandler(deviceName);

    // Initialize PacketHandler instance
    // Set the protocol version
    // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
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

void ServoHandler::closePort() {
    // Close port
    portHandler->closePort();
}

void ServoHandler::enableTorque(uint8_t id, bool enable){
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

void ServoHandler::setGoalAngle(uint8_t id, double angle) {
    //convert angle to dynamixel 
    //std::cout << angle << std::endl;
    dxl_goal_position = round(512.0 + angle * 1024.0 / 300.0);
    //std::cout << dxl_goal_position << std::endl;
    // Write goal position
    //printf("Succeeded to set the angle!\n");
    dxl_comm_result = packetHandler->write2ByteTxOnly(portHandler, id, ADDR_MX_GOAL_POSITION, dxl_goal_position);
    //dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, id, ADDR_MX_GOAL_POSITION, dxl_goal_position, &dxl_error);
    //if (dxl_comm_result != COMM_SUCCESS) {
    //    //printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    //}
    //else if (dxl_error != 0) {
    //    printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    //}
}

double ServoHandler::getPresentAngle(uint8_t id)
{
    // Read present position
    dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, id, ADDR_MX_PRESENT_POSITION, &dxl_present_position, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS){
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0){
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }

    printf("[ID:%03d]  PresPos:%03d\n", 3, dxl_present_position);
    return 0.0;
}




