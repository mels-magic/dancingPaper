/*
 * Network.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include "Network.hpp"
#include "../ParseJson/ParseJson.hpp"
#include "../../motorParameters.h"
#include "../Motor/Motor.hpp"
#include "../../boardConfig.h"
#include "../BoardAddress/BoardAddress.hpp"

void Network::init(Scheduler *userScheduler)
{
    // mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC |
    // COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
    Network::mesh.setDebugMsgTypes(ERROR | STARTUP | DEBUG); // set before init() so that you can see startup messages

    Network::mesh.init(MESH_PREFIX, MESH_PASSWORD, userScheduler, MESH_PORT);
    Network::mesh.onReceive(&receivedCallback);
    Network::mesh.onNewConnection(&newConnectionCallback);
    Network::mesh.onChangedConnections(&changedConnectionCallback);
    Network::mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

    // if you want your node to accept OTA firmware, simply include this line
    // with whatever role you want your hardware to be. For instance, a
    // mesh network may have a thermometer, rain detector, and bridge. Each of
    // those may require different firmware, so different roles are preferrable.
    //
    // MAKE SURE YOUR UPLOADED OTA FIRMWARE INCLUDES OTA SUPPORT OR YOU WILL LOSE
    // THE ABILITY TO UPLOAD MORE FIRMWARE OVER OTA. YOU ALSO WANT TO MAKE SURE
    // THE ROLES ARE CORRECT
    Network::mesh.initOTAReceive("otareceiver");
}

void Network::run()
{
    // it will run the user scheduler as well
    Network::mesh.update();
}

void Network::sendMessage(String msg)
{
    Network::mesh.sendBroadcast(msg);
}

void Network::receivedCallback(uint32_t from, String &msgStr)
{
    Serial.printf("startHere: Received from %u msg=%s\n", from, msgStr.c_str());

    message msgJson = ParseJson::deserialize(msgStr);

    if (!msgJson.isValid || !(msgJson.destAddr == BoardAddress::getAddress() || msgJson.destAddr == BROADCAST_ADDRESS))
        return;

    switch (msgJson.msgType)
    {
    case messageType::ACTION_START:
        Motor::turnOn();
        break;
    case messageType::CONFIG:
        Motor::setMotorParameters(msgJson);
        break;
    case messageType::ACTION_OFF:
        Motor::turnOff;
        break;
    case messageType::ACTION_STOP:
        Motor::stop();
        break;
    }
}

void Network::newConnectionCallback(uint32_t nodeId)
{
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void Network::changedConnectionCallback() { Serial.printf("Changed connections\n"); }

void Network::nodeTimeAdjustedCallback(int32_t offset)
{
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

painlessMesh Network::mesh;