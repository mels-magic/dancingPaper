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
    //pinMode(REMOTE_SWITCH_PIN_GND, OUTPUT);
    //digitalWrite(REMOTE_SWITCH_PIN_GND, LOW);

    RemoteControl::initChoreograpy();
}

void RemoteControl::run()
{
    Serial.println("Romote run");
    if (RemoteControl::isActive() && RemoteControl::runStatus == RemoteControl::status::OFF)
        RemoteControl::runStatus = RemoteControl::status::START_SEQUENCE_PAUSE;
    else if (!RemoteControl::isActive() && RemoteControl::runStatus != RemoteControl::status::OFF)
        RemoteControl::runStatus = RemoteControl::status::DEACTIVATING;

    RemoteControl::sequenceStep();
}

void RemoteControl::initChoreograpy()
{
    int speed[] = {150, 200, 255};
    unsigned int rampTime_ms[] = {0, 4000, 8000};
    unsigned int onTime_ms[] = {60000, 50000};
    unsigned int activationDelay_ms[] = {0, 4000, 8000};
    unsigned int addrFirstRotorInGroup[] = {1, 2, 3, 4, 6, 9, 13};

    // TODO: variation in choreogaphy
    for (int i = 0; i < MAX_ROTOR_INSTALLATION_COUNT; i++)
    {
        RemoteControl::setRotorConfig(i, 0, rampTime_ms[2], 10000, rampTime_ms[1], speed[0]);
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
    return (digitalRead(REMOTE_SWITCH_PIN) == LOW) ? true : false;
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
        RemoteControl::rotorCommand(BROADCAST_ADDRESS, messageType::ACTION_STOP);
        digitalWrite(REMOTE_LED_1_PIN, LOW);
        RemoteControl::runStatus = RemoteControl::status::OFF;
        break;
    case RemoteControl::status::START_SEQUENCE_ACTIVE:
        digitalWrite(REMOTE_LED_1_PIN, HIGH);
        RemoteControl::lastTimestamp = millis();
        RemoteControl::rotorIdxInSequence = 0;
        RemoteControl::runStatus = RemoteControl::status::SEQUENCE_ACTIVE;
        break;
    case RemoteControl::status::SEQUENCE_ACTIVE:
        if (!allUpdated)
            allUpdated = RemoteControl::sequenceActiveStep();
        if (RemoteControl::lastTimestamp + RemoteControl::sequenceActiveDuration_ms > millis())
            RemoteControl::runStatus = RemoteControl::status::START_SEQUENCE_PAUSE;
        break;
    case RemoteControl::status::START_SEQUENCE_PAUSE:
        allUpdated = false;
        RemoteControl::rotorIdxInSequence = 0;
        RemoteControl::lastTimestamp = millis();
        RemoteControl::runStatus = RemoteControl::status::SEQUENCE_PAUSE;
        break;
    case RemoteControl::status::SEQUENCE_PAUSE:
        if (!allUpdated)
            allUpdated = RemoteControl::updateRotors();
        if (RemoteControl::lastTimestamp + RemoteControl::sequencePauseDuration_ms > millis())
            RemoteControl::runStatus = RemoteControl::status::START_SEQUENCE_ACTIVE;
    }
}

bool RemoteControl::sequenceActiveStep()
{
    if (RemoteControl::lastTimestamp + RemoteControl::activationDelays_ms[RemoteControl::rotorIdxInSequence] > millis())
    {
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