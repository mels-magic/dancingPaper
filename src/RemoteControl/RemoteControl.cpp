/*
 * RemoteControl.cpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Melanie Magin
 */
#include "RemoteControl.hpp"
#include "../../boardConfig.h"
#include "../Network/Network.hpp"
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
    Serial.print("Romote run\r\n");
    // TODOs:
    // check inputs
    // update uotputs
    // send config changes
    // select and play patterns

    if (digitalRead(REMOTE_ENCODER_BUTTON_PIN))
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

    // if REMOTE_SWITCH_PIN == OFF -> stop all rotors
    // if REMOTE_SWITCH_PIN == ON  -> start running choreography sequence

    // during choreography pause: send config to all rotors
}

void RemoteControl::initChoreograpy()
{
    int speed[] = {150, 200, 255};
    unsigned int rampTime_ms[] = {0, 4000, 8000};
    unsigned int onTime_ms[] = {60000, 50000};
    unsigned int activationDelay_ms[] = {0, 4000, 8000};
    unsigned int addrFirstRotorInGroup[] = {1, 2, 3, 4, 6, 9, 13};

    RemoteControl::setRotorConfig(1, 0, rampTime_ms[2], 10000, rampTime_ms[1], speed[0]);
}

void RemoteControl::setRotorConfig(unsigned int destAddr, unsigned int activationDelay_ms, unsigned int rampUpTime_ms,
                                   unsigned int onTime_ms,
                                   unsigned int rampDownTime_ms,
                                   int speed)
{
    message msg;
    msg.srcAddr = 0;
    msg.destAddr = destAddr;
    msg.rampUpTime_ms = rampUpTime_ms;
    msg.onTime_ms = onTime_ms;
    msg.rampDownTime_ms = rampDownTime_ms;
    msg.speed = speed;

    RemoteControl::messages[destAddr];
    RemoteControl::activationDelays_ms[destAddr] = activationDelay_ms;
}

unsigned long RemoteControl::lastTimestamp;
message RemoteControl::messages[MAX_ROTOR_INSTALLATION_COUNT];
unsigned int RemoteControl::activationDelays_ms[MAX_ROTOR_INSTALLATION_COUNT];

unsigned long RemoteControl::sequenceActiveDuration_ms;
unsigned long RemoteControl::sequencePauseDuration_ms;