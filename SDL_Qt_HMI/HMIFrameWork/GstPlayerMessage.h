#ifndef GSTPLAYERMESSAGE_H
#define GSTPLAYERMESSAGE_H
#include "Interface.h"

class GstPlayerMessage:public IGstPlayerMessage
{
public:
   GstPlayerMessage();
   virtual void OnGstPlayerStatus(eGstPlayerStatus status);
};

#endif // GSTPLAYERMESSAGE_H
