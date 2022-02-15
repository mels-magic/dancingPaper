/*
 * RemoteControl.hpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Melanie Magin
 */
#pragma once

class RemoteControl
{
public:
    static void init();
    static void run();

private:
    RemoteControl() = default;

    static unsigned long lastTimestamp;
};