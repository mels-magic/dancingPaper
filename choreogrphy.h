/*
 * RemoteControl.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: Melanie Magin
 */
#pragma once

#define MAX_ROTOR_INSTALLATION_COUNT 15

#define SEQUENCE_ACTIVE_DURATION_ms 15000
#define SEQUENCE_PAUSE_DURATION_ms 5000

// activationDelays_ms, rampOnTime_ms, onTime_ms, rampOffTime_ms, speed
const long rotorDatasets[MAX_ROTOR_INSTALLATION_COUNT][5] = {
    {0, 5000, 15000, 5000, 150},
    {5000, 2000, 6000, 2000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150},
    {0, 8000, 60000, 8000, 150}};