/*
 * motorParameters.h
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

struct motorParameters
{
    unsigned int rampUpTime_ms;
    unsigned int onTime_ms;
    unsigned int rampDownTime_ms;
    byte speed;
    bool direction;
    int speedVariancePercent;
};