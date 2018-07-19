#include "SettingsEmergencyData.h"

SettingsEmergencyData* SettingsEmergencyData::m_pInst = NULL;
SettingsEmergencyData::SettingsEmergencyData()
    :m_EmergencRescueStatus("Open")
{
}

void SettingsEmergencyData::SetEmergencRescueStatus(QString status)
{
    m_EmergencRescueStatus = status;
    emit EmergencRescueStatusChange(m_EmergencRescueStatus);
}

SettingsEmergencyData *SettingsEmergencyData::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new SettingsEmergencyData();
    }
    return m_pInst;
}
