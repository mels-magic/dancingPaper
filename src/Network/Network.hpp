/*
 * Network.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once
#include <painlessMesh.h>

class Network
{
private:
    Network() = default;

public:
    static void init(Scheduler *userScheduler);
    static void run();

    static void sendMessage(String msg);

private:
    static void receivedCallback(uint32_t from, String &msg);
    static void newConnectionCallback(uint32_t nodeId);
    static void changedConnectionCallback();
    static void nodeTimeAdjustedCallback(int32_t offset);

    // Allocate the JSON document
    //
    // Inside the brackets, 256 is the RAM allocated to this document.
    // Don't forget to change this value to match your requirement.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    //static StaticJsonDocument<256> doc;
    static painlessMesh mesh;
};