/*
 * BoardAddress.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

#define ADDRESS_OF_REMOTE_CONTROLLER 254
#define BROADCAST_ADDRESS 255

class BoardAddress
{
private:
    BoardAddress() = default;

public:
    static void init();
    static int getAddress();
    static bool isRemoteControl();
};