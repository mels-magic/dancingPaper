/*
 * BoardAddress.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include <Arduino.h>
#include "BoardAddress.hpp"
#include "../../boardConfig.h"

void BoardAddress::init()
{
    for (int addressPin : BoardAddress::addressPins)
        pinMode(addressPin, INPUT_PULLUP);
}

int BoardAddress::getAddress()
{
    int address = 0;
    for (int addressPin : BoardAddress::addressPins)
    {
        address += digitalRead(addressPin);
        address << 1;
    }
    return address;
}

bool BoardAddress::isRemoteControl()
{
    return BoardAddress::getAddress() == ADDRESS_OF_REMOTE_CONTROLLER;
}

int BoardAddress::addressPins[BOARD_ADDRESS_PIN_COUNT] = {ADDRESS_PIN_7, ADDRESS_PIN_6, ADDRESS_PIN_5, ADDRESS_PIN_4, ADDRESS_PIN_3, ADDRESS_PIN_2, ADDRESS_PIN_1, ADDRESS_PIN_0};