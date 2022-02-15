/*
 * RemoteControl.hpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Melanie Magin
 */
#pragma once
#include "../../motorParameters.h"

#define MAX_ROTOR_INSTALLATION_COUNT 30

class RemoteControl
{
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

    static unsigned long lastTimestamp;
    static message messages[MAX_ROTOR_INSTALLATION_COUNT];
    static unsigned int activationDelays_ms[MAX_ROTOR_INSTALLATION_COUNT];

    static unsigned long sequenceActiveDuration_ms;
    static unsigned long sequencePauseDuration_ms;
};