/*
 * boardConfig.h
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once

#define MESH_PREFIX "whateverYouLike"
#define MESH_PASSWORD "somethingSneaky"
#define MESH_PORT 5555

#define ADDRESS_OF_REMOTE_CONTROLLER 1
#define BROADCAST_ADDRESS 255

#define ADDRESS_PIN_0 14
#define ADDRESS_PIN_1 12
#define ADDRESS_PIN_2 13
//#define ADDRESS_PIN_3 15 // has external pulldown
#define ADDRESS_PIN_3 10
#define ADDRESS_PIN_4 9
//#define ADDRESS_PIN_6 3
//#define ADDRESS_PIN_7 1

#define MOTOR_A_DIRPIN 0
#define MOTOR_A_PWM_PIN 5

#define MOTOR_B_DIRPIN 2
#define MOTOR_B_PWM_PIN 4

// #define SENSE_CONTROLLER_PIN 9
// #define ON_SWITCH_PIN 10
// #define POTI_PIN A0
// #define LED_PIN 2