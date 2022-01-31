/*
 * ParseJson.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#pragma once
#include <Arduino.h>
#include <painlessMesh.h>
#include "../../motorParameters.h"

// Allocate the JSON document
//
// Inside the brackets, 256 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use arduinojson.org/v6/assistant to compute the capacity.
#define STATIC_JSON_DOCUMENT_SIZE 256

class ParseJson
{
private:
    ParseJson() = default;

public:
    static String serialize(message params);
    static message deserialize(String msgStr);

private:
    static StaticJsonDocument<STATIC_JSON_DOCUMENT_SIZE> doc;
};