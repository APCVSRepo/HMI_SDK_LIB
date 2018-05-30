#include "SettingsDateTimeData.h"

SettingsDateTimeData* SettingsDateTimeData::m_pInst = NULL;
SettingsDateTimeData::SettingsDateTimeData()
    :m_bIs12Or24Hour(false)
{
}

void SettingsDateTimeData::SetHour12Or24(bool bHour12Or24)
{
    m_bIs12Or24Hour = bHour12Or24;
    emit Hour12Or24Change(m_bIs12Or24Hour);
}

SettingsDateTimeData *SettingsDateTimeData::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new SettingsDateTimeData();
    }
    return m_pInst;
}
