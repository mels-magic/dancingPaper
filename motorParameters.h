/*
 * motorParameters.h
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

enum class messageType
{
    CONFIG,
    ACTION_START,
    ACTION_STOP,
    ACTION_OFF
};

struct message
{
    bool isValid;
    unsigned int srcAddr;
    unsigned int destAddr;
    messageType msgType;
    unsigned int rampUpTime_ms;
    unsigned int onTime_ms;
    unsigned int rampDownTime_ms;
    int speed;
    int speedVariancePercent;
};