/*
 * Motor.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once
#include <FadeLed.h>
#include "../../motorParameters.h"

#define MOTOR_CONTROL_ELEMENT_COUNT 2

class Motor
{
private:
    Motor() = default;

public:
    static void init();
    static void setMotorParameters(motorParameters param);

    static void run();

    static void turnOn(); // ramp on time, ramp off time, on time, speed
    static void turnOff();
    static void stop();

private:
    static motorParameters param;
    static FadeLed motorControl[MOTOR_CONTROL_ELEMENT_COUNT];
    static bool isRunning;
    static unsigned long turnOffAtMillis;
};