/*
 * Network.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include "Network.hpp"
#include "../ParseJson/ParseJson.hpp"
#include "../../boardConfig.h"

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
    //String msg = "Hello from node ";
    //msg += Network::mesh.getNodeId();
    Network::mesh.sendBroadcast(msg);
    //taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SECOND * 5));
}

// Needed for painless library
void Network::receivedCallback(uint32_t from, String &msg)
{
    Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());

    // Deserialize the JSON document
    //doc.clear();
    //DeserializationError error = deserializeJson(Network::doc, msg.c_str());

    // Test if parsing succeeds.
    // if (error)
    // {
    //     Serial.print(F("deserializeJson() failed: "));
    //     Serial.println(error.f_str());
    //     return;
    // }
    // motorSpeed = doc["speed"];
    // if (motorSpeed > 255)
    //     motorSpeed = 255;
    // if (motorSpeed < -255)
    //     motorSpeed = -255;
    // motorCycleTime_sec = doc["cycleTime_sec"];
    // motorBaseDutyCycle = doc["baseDutyCycle"];
    // motorCycleJitter = doc["cycleJitter"];
    // motorDutyCycleJitter = doc["dutyCycleJitter"];
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

//StaticJsonDocument<256> Network::doc;
painlessMesh Network::mesh;