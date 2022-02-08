/*
 * ParseJson.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Melanie Magin
 */
#include "ParseJson.hpp"

String ParseJson::serialize(message params)
{
    ParseJson::doc.clear();

    ParseJson::doc["srcAddr"] = params.srcAddr;
    ParseJson::doc["destAddr"] = params.destAddr;
    ParseJson::doc["msgType"] = (int)params.msgType;

    ParseJson::doc["rampUpTime_ms"] = params.rampUpTime_ms;
    ParseJson::doc["onTime_ms"] = params.onTime_ms;
    ParseJson::doc["rampDownTime_ms"] = params.rampDownTime_ms;
    ParseJson::doc["speed"] = params.speed;
    ParseJson::doc["speedVariancePercent"] = params.speedVariancePercent;

    String ret;
    serializeJson(ParseJson::doc, ret);
    return ret;
}

message ParseJson::deserialize(String msgStr)
{
    message params;

    ParseJson::doc.clear();
    DeserializationError error = deserializeJson(ParseJson::doc, msgStr.c_str());

    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        params.isValid = false;
        return params;
    }

    params.srcAddr = ParseJson::doc["srcAddr"];
    params.destAddr = ParseJson::doc["destAddr"];
    int tmpMsgType = ParseJson::doc["msgType"];;
    params.msgType = (messageType)tmpMsgType;

    params.rampUpTime_ms = ParseJson::doc["rampUpTime_ms"];
    params.onTime_ms = ParseJson::doc["onTime_ms"];
    params.rampDownTime_ms = ParseJson::doc["rampDownTime_ms"];
    params.speed = ParseJson::doc["speed"];
    params.speedVariancePercent = ParseJson::doc["speedVariancePercent"];

    params.isValid = true;

    return params;
}

StaticJsonDocument<STATIC_JSON_DOCUMENT_SIZE> ParseJson::doc;