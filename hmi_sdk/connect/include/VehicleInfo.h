#ifndef VEHICLEINFOCLIENT_H
#define VEHICLEINFOCLIENT_H

#include <json/json.h>

#include "ISocketManager.h"
#include "Channel.h"

class VehicleInfo : public Channel
{
public:
    VehicleInfo();
    ~VehicleInfo();
virtual ID_CHN_TYPE ChannelType() {return ID_CHN_VEHICLE;}
protected:
    void onRequest(Json::Value &);

private:
    bool getVehicleData(Json::Value &,Json::Value &result);
    Json::Value vehicleInfoGetDTCsResponse(Json::Value &);
    Json::Value vehicleInfoReadDIDResponse(Json::Value &);
};

#endif // VEHICLEINFOCLIENT_H
