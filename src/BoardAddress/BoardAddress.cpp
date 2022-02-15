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
}

int BoardAddress::getAddress()
{
    if (IS_REMOTE_CONTROLLER)
        return ADDRESS_OF_REMOTE_CONTROLLER;
    return ADDRESS_NUMBERR_ON_LABEL;
}

bool BoardAddress::isRemoteControl()
{
    return IS_REMOTE_CONTROLLER;
}