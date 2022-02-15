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
    pinMode(REMOTE_LED_1_PIN, OUTPUT);
    pinMode(REMOTE_SWITCH_PIN, INPUT_PULLUP);

    RemoteControl::initChoreograpy();
}

void RemoteControl::run()
{
    if (RemoteControl::isActive() && RemoteControl::runStatus == RemoteControl::status::OFF)
        RemoteControl::runStatus = RemoteControl::status::START_SEQUENCE_PAUSE;
    else if (!RemoteControl::isActive() && RemoteControl::runStatus != RemoteControl::status::OFF)
        RemoteControl::runStatus = RemoteControl::status::DEACTIVATING;

    RemoteControl::sequenceStep();
}

void RemoteControl::initChoreograpy()
{
    RemoteControl::sequenceActiveDuration_ms = 15000;
    RemoteControl::sequencePauseDuration_ms = 5000;

    // activationDelays_ms, rampOnTime_ms, onTime_ms, rampOffTime_ms, speed
    long rotorDatasets[MAX_ROTOR_INSTALLATION_COUNT][5] = {
        {0, 5000, 15000, 5000, 150},
        {5000, 2000, 6000, 2000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150},
        {0, 8000, 60000, 8000, 150}};

    for (int i = 0; i < MAX_ROTOR_INSTALLATION_COUNT; i++)
    {
        RemoteControl::setRotorConfig(i,
                                      rotorDatasets[i][0],
                                      rotorDatasets[i][1],
                                      rotorDatasets[i][2],
                                      rotorDatasets[i][3],
                                      rotorDatasets[i][4]);
    }
}

void RemoteControl::setRotorConfig(unsigned int destAddr, unsigned int activationDelay_ms, unsigned int rampUpTime_ms,
                                   unsigned int onTime_ms,
                                   unsigned int rampDownTime_ms,
                                   int speed)
{
    message msg;
    msg.srcAddr = ADDRESS_OF_REMOTE_CONTROLLER;
    msg.destAddr = destAddr;
    msg.msgType = messageType::CONFIG;
    msg.rampUpTime_ms = rampUpTime_ms;
    msg.onTime_ms = onTime_ms;
    msg.rampDownTime_ms = rampDownTime_ms;
    msg.speed = speed;

    RemoteControl::messages[destAddr];
    RemoteControl::activationDelays_ms[destAddr] = activationDelay_ms;
}

bool RemoteControl::isActive()
{
    return (digitalRead(REMOTE_SWITCH_PIN) == LOW) ? false : true;
}

bool RemoteControl::updateRotors()
{
    Network::sendMessage(RemoteControl::messages[RemoteControl::rotorIdxInSequence]);

    RemoteControl::rotorIdxInSequence++;
    if (RemoteControl::rotorIdxInSequence >= MAX_ROTOR_INSTALLATION_COUNT)
        return true;
    return false;
}

void RemoteControl::rotorCommand(unsigned int rotorIdx, messageType command)
{
    message msg;
    msg.srcAddr = ADDRESS_OF_REMOTE_CONTROLLER;
    msg.destAddr = (rotorIdx >= BROADCAST_ADDRESS) ? BROADCAST_ADDRESS : rotorIdx;
    msg.msgType = command;
    Network::sendMessage(msg);
}

void RemoteControl::sequenceStep()
{
    static bool allUpdated = false;
    switch (RemoteControl::runStatus)
    {
    case RemoteControl::status::OFF:
        break;
    case RemoteControl::status::DEACTIVATING:
        Serial.println("Remote: DEACTIVATING");
        RemoteControl::rotorCommand(BROADCAST_ADDRESS, messageType::ACTION_STOP);
        digitalWrite(REMOTE_LED_1_PIN, LOW);
        RemoteControl::runStatus = RemoteControl::status::OFF;
        break;
    case RemoteControl::status::START_SEQUENCE_ACTIVE:
        Serial.println("Remote: START_SEQUENCE_ACTIVE");
        digitalWrite(REMOTE_LED_1_PIN, HIGH);
        allUpdated = false;
        RemoteControl::lastTimestamp = millis();
        RemoteControl::rotorIdxInSequence = 0;
        RemoteControl::runStatus = RemoteControl::status::SEQUENCE_ACTIVE;
        break;
    case RemoteControl::status::SEQUENCE_ACTIVE:
        if (!allUpdated)
            allUpdated = RemoteControl::sequenceActiveStep();
        if (RemoteControl::lastTimestamp + RemoteControl::sequenceActiveDuration_ms < millis())
            RemoteControl::runStatus = RemoteControl::status::START_SEQUENCE_PAUSE;
        break;
    case RemoteControl::status::START_SEQUENCE_PAUSE:
        Serial.println("Remote: START_SEQUENCE_PAUSE");
        allUpdated = false;
        RemoteControl::rotorIdxInSequence = 0;
        RemoteControl::lastTimestamp = millis();
        RemoteControl::runStatus = RemoteControl::status::SEQUENCE_PAUSE;
        break;
    case RemoteControl::status::SEQUENCE_PAUSE:
        if (!allUpdated)
            allUpdated = RemoteControl::updateRotors();
        if (RemoteControl::lastTimestamp + RemoteControl::sequencePauseDuration_ms < millis())
            RemoteControl::runStatus = RemoteControl::status::START_SEQUENCE_ACTIVE;
        break;
    default:
        RemoteControl::runStatus = RemoteControl::status::DEACTIVATING;
    }
    static bool doPrintStr = true;
    if (allUpdated && doPrintStr)
    {
        Serial.println("allUpdated");
        doPrintStr = false;
    }
    if (!allUpdated)
        doPrintStr = true;

    // unsigned long msInState = millis() - RemoteControl::lastTimestamp;
    // if (msInState % 1000 == 0)
    // {
    //     unsigned long msRemaining = 0;
    //     if (RemoteControl::runStatus == RemoteControl::status::SEQUENCE_PAUSE)
    //     {
    //         msRemaining = RemoteControl::sequencePauseDuration_ms - msInState;
    //         Serial.print("SEQUENCE_PAUSE: seconds remaining: ");
    //     }
    //     else if (RemoteControl::runStatus == RemoteControl::status::SEQUENCE_ACTIVE)
    //     {
    //         msRemaining = RemoteControl::sequenceActiveDuration_ms - msInState;
    //         Serial.print("SEQUENCE_ACTIVE: seconds remaining: ");
    //     }
    //     Serial.println(msRemaining / 1000);
    // }
}

bool RemoteControl::sequenceActiveStep()
{
    if (RemoteControl::lastTimestamp + RemoteControl::activationDelays_ms[RemoteControl::rotorIdxInSequence] > millis())
    {
        Serial.print("ACTION_START for rotor ");
        Serial.println(RemoteControl::rotorIdxInSequence);
        RemoteControl::rotorCommand(RemoteControl::rotorIdxInSequence, messageType::ACTION_START);
        RemoteControl::rotorIdxInSequence++;
        if (RemoteControl::rotorIdxInSequence >= MAX_ROTOR_INSTALLATION_COUNT)
            return true;
    }
    return false;
}

unsigned long RemoteControl::lastTimestamp;
message RemoteControl::messages[MAX_ROTOR_INSTALLATION_COUNT];
unsigned int RemoteControl::activationDelays_ms[MAX_ROTOR_INSTALLATION_COUNT];

unsigned long RemoteControl::sequenceActiveDuration_ms;
unsigned long RemoteControl::sequencePauseDuration_ms;

unsigned int RemoteControl::rotorIdxInSequence;
RemoteControl::status RemoteControl::runStatus;