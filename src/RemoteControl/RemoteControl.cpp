/*
 * RemoteControl.cpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Melanie Magin
 */
#include "RemoteControl.hpp"
#include "../../boardConfig.h"
#include "../Network/Network.hpp"
#include "../../motorParameters.h"
#include "../BoardAddress/BoardAddress.hpp"
#include <Arduino.h>

void RemoteControl::init()
{
    RemoteControl::lastTimestamp = millis();
    // TODO: init IO
    pinMode(REMOTE_LED_1_PIN, OUTPUT);
    pinMode(REMOTE_LED_2_PIN, OUTPUT);
    pinMode(REMOTE_LED_3_PIN, OUTPUT);
    pinMode(REMOTE_LED_4_PIN, OUTPUT);
    pinMode(REMOTE_LED_5_PIN, OUTPUT);

    pinMode(REMOTE_SWITCH_PIN, INPUT);
    pinMode(REMOTE_ENCODER_BUTTON_PIN, INPUT);
    pinMode(REMOTE_ENCODER_PIN_1, INPUT);
    pinMode(REMOTE_ENCODER_PIN_2, INPUT);
}

void RemoteControl::run()
{
    message msg;
    msg.srcAddr = 0;
    msg.destAddr = BROADCAST_ADDRESS;
    msg.msgType = messageType::ACTION_START;
    Serial.print("Romote run\r\n");
    if (digitalRead(REMOTE_ENCODER_BUTTON_PIN))
        Network::sendMessage(msg);
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