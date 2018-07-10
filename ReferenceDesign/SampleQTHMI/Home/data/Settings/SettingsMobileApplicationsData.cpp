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
    if(NULL == m_pInst)
    {
        m_pInst = new SettingsMobileApplicationsData();
    }
    return m_pInst;
}
