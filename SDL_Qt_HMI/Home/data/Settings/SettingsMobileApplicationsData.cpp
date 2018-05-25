#include "SettingsMobileApplicationsData.h"

SettingsMobileApplicationsData* SettingsMobileApplicationsData::m_pInst = NULL;
SettingsMobileApplicationsData::SettingsMobileApplicationsData()
    :m_MobileApplicationsStatus("Open")
{
}

void SettingsMobileApplicationsData::SetMobileApplicationsStatus(QString status)
{
    m_MobileApplicationsStatus = status;
    emit MobileApplicationsStatusChange(m_MobileApplicationsStatus);
}

SettingsMobileApplicationsData *SettingsMobileApplicationsData::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new SettingsMobileApplicationsData();
    }
    return m_pInst;
}
