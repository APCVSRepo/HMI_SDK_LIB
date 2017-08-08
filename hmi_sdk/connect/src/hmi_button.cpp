#include "hmi_button.h"
#include <iostream>
#include <string>
#include "json/json.h"
#include "global_first.h"

Buttons::Buttons() : Channel(200,"Buttons")
{

}

Buttons::~Buttons()
{

}


void Buttons::onRequest(Json::Value &request)
{
    std::string method = request["method"].asString();
    int  id = request["id"].asInt();
    if (method == "Buttons.GetCapabilities") {
        sendResult(id,"GetCapabilities");
    }else if (method == "Buttons.IsReady") {
        sendResult(id,"IsReady");
    } else {
        Channel::onRequest(request);
    }
}

