#include "SettingsDisplayData.h"


SettingsDisplayData* SettingsDisplayData::m_pInst = NULL;
SettingsDisplayData::SettingsDisplayData()
    :m_pattern("Auto")
{
}

void SettingsDisplayData::SetPattern(QString pattern)
{
    m_pattern = pattern;
    emit PatternChannge(m_pattern);
}

SettingsDisplayData *SettingsDisplayData::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new SettingsDisplayData();
    }
    return m_pInst;
}
