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
    if(m_pInst == NULL)
    {
        m_pInst = new SettingsRoutineSettingData();
    }
    return m_pInst;
}
