/*
 * BoardAddress.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

#define BOARD_ADDRESS_PIN_COUNT 8

class BoardAddress
{
private:
    BoardAddress() = default;

public:
    static void init();
    static int getAddress();

private:
    static int addressPins[BOARD_ADDRESS_PIN_COUNT];
};