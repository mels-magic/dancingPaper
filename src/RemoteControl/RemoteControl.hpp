/*
 * RemoteControl.hpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Melanie Magin
 */
#pragma once
#include "../../motorParameters.h"
#include "../../choreogrphy.h"

class RemoteControl
{
private:
    enum class status
    {
        OFF,
        DEACTIVATING,
        START_SEQUENCE_ACTIVE,
        SEQUENCE_ACTIVE,
        START_SEQUENCE_PAUSE,
        SEQUENCE_PAUSE
    };

public:
    static void init();
    static void run();

private:
    RemoteControl() = default;

    static void initChoreograpy();

    static void setRotorConfig(unsigned int destAddr, unsigned int activationDelay_ms, unsigned int rampUpTime_ms,
                               unsigned int onTime_ms,
                               unsigned int rampDownTime_ms,
                               int speed);

    static bool isActive();
    static bool updateRotors();
    static void rotorCommand(unsigned int rotorIdx, messageType command);

    static void sequenceStep();
    static bool sequenceActiveStep();

    static unsigned long lastTimestamp;
    static message messages[MAX_ROTOR_INSTALLATION_COUNT];
    static unsigned int activationDelays_ms[MAX_ROTOR_INSTALLATION_COUNT];

    static unsigned long sequenceActiveDuration_ms;
    static unsigned long sequencePauseDuration_ms;

    static unsigned int rotorIdxInSequence;

    static status runStatus;
};