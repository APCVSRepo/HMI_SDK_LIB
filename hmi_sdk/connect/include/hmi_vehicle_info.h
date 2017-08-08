#ifndef VEHICLE_INFO_H_
#define VEHICLE_INFO_H_

#include "hmi_channel.h"

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

#endif // VEHICLE_INFO_H_
