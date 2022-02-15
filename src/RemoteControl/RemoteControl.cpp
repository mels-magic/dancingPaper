/*
 * RemoteControl.cpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Melanie Magin
 */
#include "RemoteControl.hpp"
#include "../Network/Network.hpp"
#include "../../motorParameters.h"
#include "../BoardAddress/BoardAddress.hpp"
#include <Arduino.h>

void RemoteControl::init()
{
    RemoteControl::lastTimestamp = millis();
    // TODO: init IO
}

void RemoteControl::run()
{
    Serial.print("Romote run\r\n");
    // TODOs:
    // check inputs
    // update uotputs
    // send config changes
    // select and play patterns

    if (RemoteControl::lastTimestamp + 20000 < millis())
    {
        RemoteControl::lastTimestamp = millis();
        // struct message
        // {
        //     bool isValid;
        //     unsigned int srcAddr;
        //     unsigned int destAddr;
        //     messageType msgType;
        //     unsigned int rampUpTime_ms;
        //     unsigned int onTime_ms;
        //     unsigned int rampDownTime_ms;
        //     int speed;
        //     int speedVariancePercent;
        // };
        message msg;
        msg.srcAddr = 1;
        msg.destAddr = BROADCAST_ADDRESS;
        msg.msgType = messageType::ACTION_START;

        Network::sendMessage(msg);
    }
}

unsigned long RemoteControl::lastTimestamp;