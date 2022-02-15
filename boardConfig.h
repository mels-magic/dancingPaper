/*
 * boardConfig.h
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

// set per devicebefore flashing:
#define ADDRESS_NUMBERR_ON_LABEL 2
#define IS_REMOTE_CONTROLLER true // set true / false

#define MESH_PREFIX "whateverYouLike"
#define MESH_PASSWORD "somethingSneaky"
#define MESH_PORT 5555

// #define ADDRESS_PIN_0 14 // D5
// #define ADDRESS_PIN_1 12 // D6
// #define ADDRESS_PIN_2 13 // D7
// //#define ADDRESS_PIN_3 15 // D8 -- has external pulldown
// #define ADDRESS_PIN_3 10 // SD3
// #define ADDRESS_PIN_4 9 // SD2

// #define ADDRESS_PIN_REMOTE 6 // SDCLK / CLK
// #define ADDRESS_PIN_REMOTE_GND 7 // SDD0 / SD0 / MISO
#define REMOTE_SWITCH_PIN 11 // SDCMD / CMD / MOSI
// #define REMOTE_SWITCH_PIN_GND 8 // SDD1 / SD1 / INT

#define MOTOR_A_DIRPIN 0 // D3
#define MOTOR_A_PWM_PIN 5 // D1

#define MOTOR_B_DIRPIN 2 // D4, also LED near antenna
#define MOTOR_B_PWM_PIN 4 // D2

#define REMOTE_LED_1_PIN 16  // onboard LED near USB connector