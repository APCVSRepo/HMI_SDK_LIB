#include "SettingsRoutineSettingData.h"


SettingsRoutineSettingData* SettingsRoutineSettingData::m_pInst = NULL;
SettingsRoutineSettingData::SettingsRoutineSettingData()
    :m_language("English")
{
}

void SettingsRoutineSettingData::SetLanguage(QString language)
{
    m_language = language;
    emit LanguageChannge(m_language);
}

SettingsRoutineSettingData *SettingsRoutineSettingData::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new SettingsRoutineSettingData();
    }
    return m_pInst;
}
