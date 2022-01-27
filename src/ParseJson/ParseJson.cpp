/*
 * ParseJson.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include "ParseJson.hpp"

String ParseJson::serialize(motorParameters params)
{
    ParseJson::doc.clear();

    ParseJson::doc["rampUpTime_ms"] = params.rampUpTime_ms;
    ParseJson::doc["onTime_ms"] = params.onTime_ms;
    ParseJson::doc["rampDownTime_ms"] = params.rampDownTime_ms;
    ParseJson::doc["speed"] = params.speed;
    ParseJson::doc["direction"] = params.direction;
    ParseJson::doc["speedVariancePercent"] = params.speedVariancePercent;

    String ret;
    serializeJson(ParseJson::doc, ret);
    return ret;
}

motorParameters ParseJson::deserialize(String msg)
{
    motorParameters params;

    ParseJson::doc.clear();
    DeserializationError error = deserializeJson(ParseJson::doc, msg.c_str());

    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return params;
    }

    params.rampUpTime_ms = ParseJson::doc["rampUpTime_ms"];
    params.onTime_ms = ParseJson::doc["onTime_ms"];
    params.rampDownTime_ms = ParseJson::doc["rampDownTime_ms"];
    params.speed = ParseJson::doc["speed"];
    params.direction = ParseJson::doc["direction"];
    params.speedVariancePercent = ParseJson::doc["speedVariancePercent"];

    return params;
}

StaticJsonDocument<STATIC_JSON_DOCUMENT_SIZE> ParseJson::doc;