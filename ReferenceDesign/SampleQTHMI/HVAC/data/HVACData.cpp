#include "HVACData.h"
#include "HVAC/app/HVAC.h"
HVACData* HVACData::m_pInst = NULL;
HVACData::HVACData()
    :m_iZone(HVAC_FRONT_LEFT_RIGRT_AND_REAR_ZONE)
{
}

void HVACData::SetZone(int zone)
{
    m_iZone = zone;
    emit SigZone(zone);
}

int HVACData::GetZone()
{
    return m_iZone;
}



HVACData *HVACData::Inst()
{
    if(NULL == m_pInst )
    {
        m_pInst = new HVACData();
    }
    return m_pInst;
}
