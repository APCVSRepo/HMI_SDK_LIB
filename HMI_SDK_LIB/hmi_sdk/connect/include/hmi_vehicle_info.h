/**
* @file			hmi_vehicle_info
* @brief		汽车信息通道，处理SDL发送的VehicleInfo相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef VEHICLE_INFO_H_
#define VEHICLE_INFO_H_

#include "hmi_channel.h"

namespace hmisdk {

class VehicleInfo : public Channel {
 public:
  VehicleInfo();
  ~VehicleInfo();
  virtual ID_CHN_TYPE ChannelType() {return ID_CHN_VEHICLE;}
 protected:
  void onRequest(Json::Value &);

 private:
  bool getVehicleData(Json::Value &, Json::Value &result);
  Json::Value vehicleInfoGetDTCsResponse(Json::Value &);
  Json::Value vehicleInfoReadDIDResponse(Json::Value &);
};

}

#endif // VEHICLE_INFO_H_
