/*
 * Motor.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once
#include "../../motorParameters.h"

#define MOTOR_FADE_TIME_DELTA_MS 100

class Motor
{
private:
    Motor() = default;

public:
    static void init();
    static void setMotorParameters(message param);

    static void run();

    static void turnOn();
    static void turnOff();
    static void stop();

private:
    static void fade();

    static message param;
    static bool isRunning;
    static unsigned long turnOffAtMillis;
    static unsigned long lastTimestamp;
    static int fadeIncrement;
    static int currentSpeed;
    static int targetSpeed;
};