/*
 * BoardAddress.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

#define ADDRESS_OF_REMOTE_CONTROLLER 1
#define BROADCAST_ADDRESS 255

#define BOARD_ADDRESS_PIN_COUNT 5

class BoardAddress
{
private:
    BoardAddress() = default;

public:
    static void init();
    static int getAddress();
    static bool isRemoteControl();

private:
    static int addressPins[BOARD_ADDRESS_PIN_COUNT];
};