#include <Navigation.h>
#include <iostream>
#include <string>
#include "json/json.h"

Navigation::Navigation() : Channel(800,"Navigation")
{

}

Navigation::~Navigation()
{

}


void Navigation::onRequest(Json::Value &request)
{
    std::string method = request["method"].asString();
    int  id = request["id"].asInt();
    if (method == "Navigation.IsReady") {
        sendResult(id,"IsReady");
    }else if (method == "Navigation.ShowConstantTBT") {
        sendResult(id,"ShowConstantTBT");
    }else if (method == "Navigation.UpdateTurnList") {
        sendResult(id,"UpdateTurnList");
    }else if (method == "Navigation.AlertManeuver") {
        sendResult(id,"AlertManeuver");
    }else if (method == "Navigation.StartStream") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"StartStream",result);
    }else if (method == "Navigation.StopStream") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"StopStream",result);
    }else if (method == "Navigation.StartAudioStream") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"StartAudioStream",result);
    }else if (method == "Navigation.StopAudioStream") {
        Result result = m_pCallback->onRequest(request);
        sendResult(id,"StopAudioStream",result);
    }else {
        Channel::onRequest(request);
    }
}
