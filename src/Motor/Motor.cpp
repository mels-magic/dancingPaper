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
    pinMode(MOTOR_A_PWM_PIN, OUTPUT);
    pinMode(MOTOR_B_PWM_PIN, OUTPUT);

    digitalWrite(MOTOR_A_DIRPIN, LOW);
    digitalWrite(MOTOR_B_DIRPIN, LOW);

    Motor::param.onTime_ms = 15000;
    Motor::param.rampDownTime_ms = 5000;
    Motor::param.rampUpTime_ms = 5000;
    Motor::param.speed = 200;
    Motor::param.speedVariancePercent = 0;

    Serial.print("Init motor.\r\n");
    Motor::turnOn();
    Motor::lastTimestamp = millis();
}

void Motor::setMotorParameters(message param)
{
    Motor::param = param;
    Serial.print("M_setParam\r\n");
}

void Motor::run()
{
    if (Motor::isRunning && Motor::turnOffAtMillis < millis())
        Motor::turnOff();

    static int val = 0;
    if (Motor::lastTimestamp + MOTOR_FADE_TIME_DELTA_MS < millis())
    {
        Motor::lastTimestamp = millis();
        Motor::fade();
    }
}

void Motor::turnOn()
{
    Serial.print("turnOn\r\n");
    Motor::isRunning = true;

    Motor::turnOffAtMillis = millis() + Motor::param.onTime_ms;
    Motor::targetSpeed = (Motor::param.speed < 255) ? Motor::param.speed : 255;
    int intervals = Motor::param.rampUpTime_ms / MOTOR_FADE_TIME_DELTA_MS;
    Motor::fadeIncrement = Motor::targetSpeed / intervals;
    Motor::fadeIncrement = (Motor::fadeIncrement > 0) ? Motor::fadeIncrement : 1;
}

void Motor::turnOff()
{
    Serial.print("turnOff\r\n");
    Motor::isRunning = false;
    
    Motor::targetSpeed = 0;
    int intervals = Motor::param.rampUpTime_ms / MOTOR_FADE_TIME_DELTA_MS;
    Motor::fadeIncrement = Motor::currentSpeed / intervals;
    Motor::fadeIncrement = (Motor::fadeIncrement > 0) ? Motor::fadeIncrement : 1;
}

void Motor::stop()
{
    Serial.print("stop\r\n");
    digitalWrite(MOTOR_A_DIRPIN, LOW);
    digitalWrite(MOTOR_B_DIRPIN, LOW);
    digitalWrite(MOTOR_A_PWM_PIN, LOW);
    digitalWrite(MOTOR_B_PWM_PIN, LOW);

    Motor::currentSpeed = 0;
    Motor::targetSpeed = 0;
}

void Motor::fade()
{
    Serial.print("\r\n");
    Serial.print("current:");
    Serial.print(Motor::currentSpeed);
    Serial.print(",");
    Serial.print("target:");
    Serial.print(Motor::targetSpeed);
    Serial.print("\r\n");
    if (Motor::currentSpeed == Motor::targetSpeed)
        return;

    int direction = (Motor::targetSpeed - Motor::currentSpeed >= 0) ? 1 : -1;
    int increment = fadeIncrement * direction;
    Motor::currentSpeed += increment;

    if (abs(Motor::targetSpeed - Motor::currentSpeed) < abs(increment / 2))
        Motor::currentSpeed = Motor::targetSpeed;

    if (Motor::currentSpeed > 0)
    {
        digitalWrite(MOTOR_A_DIRPIN, HIGH);
        digitalWrite(MOTOR_B_DIRPIN, HIGH);
    }
    else
    {
        digitalWrite(MOTOR_A_DIRPIN, LOW);
        digitalWrite(MOTOR_B_DIRPIN, LOW);
    }
    analogWrite(MOTOR_A_PWM_PIN, abs(Motor::currentSpeed));
    analogWrite(MOTOR_B_PWM_PIN, abs(Motor::currentSpeed));
    analogWrite(16, abs(Motor::currentSpeed));
}

message Motor::param;
bool Motor::isRunning;
unsigned long Motor::turnOffAtMillis;
unsigned long Motor::lastTimestamp;
int Motor::fadeIncrement;
int Motor::currentSpeed;
int Motor::targetSpeed;