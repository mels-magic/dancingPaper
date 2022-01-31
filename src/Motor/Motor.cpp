/*
 * Motor.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include "Motor.hpp"
#include "../../boardConfig.h"

void Motor::init()
{
    Motor::turnOffAtMillis = 0;
    Motor::isRunning = false;

    pinMode(MOTOR_A_DIRPIN, OUTPUT);
    pinMode(MOTOR_B_DIRPIN, OUTPUT);

    digitalWrite(MOTOR_A_DIRPIN, LOW);
    digitalWrite(MOTOR_B_DIRPIN, LOW);

    for (FadeLed motorController : Motor::motorControl)
    {
        motorController.begin(0);
    }
}

void Motor::setMotorParameters(message param)
{
    Motor::param = param;
}

void Motor::run()
{
    FadeLed::update();

    if (Motor::isRunning && Motor::turnOffAtMillis < millis())
        Motor::turnOff();
}

void Motor::turnOn()
{
    Motor::isRunning = true;
    if (Motor::param.direction)
    {
        digitalWrite(MOTOR_A_DIRPIN, LOW);
        digitalWrite(MOTOR_B_DIRPIN, LOW);
    }
    else
    {
        digitalWrite(MOTOR_A_DIRPIN, HIGH);
        digitalWrite(MOTOR_B_DIRPIN, HIGH);
    }

    Motor::turnOffAtMillis = millis() + Motor::param.onTime_ms;

    for (FadeLed motorController : Motor::motorControl)
    {
        motorController.setTime(Motor::param.rampUpTime_ms, true);
        motorController.set(Motor::param.speed);
    }
}

void Motor::turnOff()
{
    Motor::isRunning = false;
    for (FadeLed motorController : Motor::motorControl)
    {
        motorController.setTime(Motor::param.rampDownTime_ms, true);
        motorController.off();
    }
}

void Motor::stop()
{
    for (FadeLed motorController : Motor::motorControl)
        motorController.begin(0);
}

message Motor::param;
FadeLed Motor::motorControl[MOTOR_CONTROL_ELEMENT_COUNT] = {MOTOR_A_PWN_PIN, MOTOR_B_PWM_PIN};
bool Motor::isRunning;
unsigned long Motor::turnOffAtMillis;