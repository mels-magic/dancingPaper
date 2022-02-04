/*
 * Motor.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include "Motor.hpp"
#include <Arduino.h>
#include "../../boardConfig.h"

void Motor::init()
{
    Motor::turnOffAtMillis = 0;
    Motor::isRunning = false;

    pinMode(16, OUTPUT);
    pinMode(MOTOR_A_DIRPIN, OUTPUT);
    pinMode(MOTOR_B_DIRPIN, OUTPUT);
    pinMode(MOTOR_A_PWN_PIN, OUTPUT);
    pinMode(MOTOR_B_PWM_PIN, OUTPUT);

    digitalWrite(MOTOR_A_DIRPIN, LOW);
    digitalWrite(MOTOR_B_DIRPIN, LOW);

    Motor::param.onTime_ms = 10000;
    Motor::param.rampDownTime_ms = 50;
    Motor::param.rampUpTime_ms = 50;
    Motor::param.direction = false;
    Motor::param.speed = 50;
    Motor::param.speedVariancePercent = 0;

    // for (FadeLed motorController : Motor::motorControl)
    // {
    // //    motorController.begin(0);
    //     Serial.print("x ");
    // }

    Motor::turnOn();
    Serial.print("Init motor.\r\n");
    Motor::lastTimestamp = millis();
}

void Motor::setMotorParameters(message param)
{
    Motor::param = param;
    Serial.print("M_setParam\r\n");
}

void Motor::run()
{
    //FadeLed::update();

    if (Motor::isRunning && Motor::turnOffAtMillis < millis())
        Motor::turnOff();

    static int val = 0;
    if(Motor::lastTimestamp + 1000 < millis())
    {
        analogWrite(16,val);
        analogWrite(5,val);
        analogWrite(4,val);
        
        val += 1;
        if(val > 200)
            val = 0;
    }
}

void Motor::turnOn()
{
    Serial.print("turnOn\r\n");
    Motor::isRunning = true;
    // if (Motor::param.direction)
    // {
    //     digitalWrite(MOTOR_A_DIRPIN, LOW);
    //     digitalWrite(MOTOR_B_DIRPIN, LOW);
    // }
    // else
    // {
        digitalWrite(MOTOR_A_DIRPIN, HIGH);
        digitalWrite(MOTOR_B_DIRPIN, HIGH);
    //}

    Motor::turnOffAtMillis = millis() + Motor::param.onTime_ms;

    for (FadeLed motorController : Motor::motorControl)
    {
        motorController.setTime(Motor::param.rampUpTime_ms, true);
        motorController.set(Motor::param.speed);
    }
    //Motor::motorControl[0].setTime(Motor::param.rampUpTime_ms, true);
    //Motor::motorControl[0].set(Motor::param.speed);
    //Motor::motorControl[1].setTime(Motor::param.rampUpTime_ms, true);
    //Motor::motorControl[1].set(Motor::param.speed);
}

void Motor::turnOff()
{
    Serial.print("turnOff\r\n");
    Motor::isRunning = false;
    for (FadeLed motorController : Motor::motorControl)
    {
        motorController.setTime(Motor::param.rampDownTime_ms, true);
        motorController.off();
    }
    digitalWrite(MOTOR_A_DIRPIN, LOW);
    digitalWrite(MOTOR_B_DIRPIN, LOW);
}

void Motor::stop()
{
    Serial.print("stop\r\n");
    for (FadeLed motorController : Motor::motorControl)
        motorController.begin(0);
}

message Motor::param;
FadeLed Motor::motorControl[MOTOR_CONTROL_ELEMENT_COUNT] = {MOTOR_A_PWN_PIN, MOTOR_B_PWM_PIN};
bool Motor::isRunning;
unsigned long Motor::turnOffAtMillis;
unsigned long Motor::lastTimestamp;