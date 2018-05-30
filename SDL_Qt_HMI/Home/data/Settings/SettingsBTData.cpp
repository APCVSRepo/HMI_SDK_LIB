#include "SettingsBTData.h"

SettingsBTData *SettingsBTData::s_pInstance = NULL;

SettingsBTData *SettingsBTData::GetInstance()
{
    if(NULL == s_pInstance)
    {
        s_pInstance = new SettingsBTData;
    }
    return s_pInstance;
}

SettingsBTData::SettingsBTData(QObject *parent)
    :QObject(parent)
{
    BTDeviceInfo info1;
    info1.id = 1;
    info1.name = "JBL";
    info1.status = BTStatus_CONNECTED;
    info1.address = "01:01:01:01:01:01";
    info1.pin = 1111;
    m_BTPairedList.push_back(info1);

    BTDeviceInfo info2;
    info2.id = 2;
    info2.name = "HUAWEI mobile phone";
    info2.status = BTStatus_CONNECTING;
    info2.address = "01:01:01:01:01:01";
    info2.pin = 0001;
    m_BTPairedList.push_back(info2);

    BTDeviceInfo info3;
    info3.id = 3;
    info3.name = "XiaoMi 3333";
    info3.status = BTStatus_PAIRED;
    info3.address = "01:01:01:01:01:01";
    info3.pin = 3333;
    m_BTPairedList.push_back(info3);

    BTDeviceInfo info4;
    info4.id = 4;
    info4.name = "Nokia 4444";
    info4.status = BTStatus_PAIRED;
    info4.address = "01:01:01:01:01:01";
    info4.pin = 4444;
    m_BTPairedList.push_back(info4);

    BTDeviceInfo info5;
    info5.id = 5;
    info5.name = "JBL_VeryLong123456789012345678901234567890";
    info5.status = BTStatus_NORMAL;
    info5.address = "01:01:01:01:01:01";
    info5.pin = 1234;
    m_BTSearchList.push_back(info5);

    BTDeviceInfo info6;
    info6.id = 6;
    info6.name = "JBL6666";
    info6.status = BTStatus_NORMAL;
    info6.address = "01:01:01:01:01:01";
    info6.pin = 6666;
    m_BTSearchList.push_back(info6);

    BTDeviceInfo info7;
    info7.id = 7;
    info7.name = "JBL7777";
    info7.status = BTStatus_NORMAL;
    info7.address = "01:01:01:01:01:01";
    info7.pin = 7777;
    m_BTSearchList.push_back(info7);
}

const BTDeviceInfo &SettingsBTData::GetBTPairedListInfo(int index) const
{
    return m_BTPairedList[index];
}

int SettingsBTData::GetBTPairedListSize() const
{
    return m_BTPairedList.size();
}

const BTDeviceInfo &SettingsBTData::GetBTSearchListInfo(int index) const
{
    return m_BTSearchList[index];
}

int SettingsBTData::GetBTSearchListSize() const
{
    return m_BTSearchList.size();
}

void SettingsBTData::SetSelectedBTInfo(const BTDeviceInfo &info)
{
    m_selectedBTInfo = info;
}

const BTDeviceInfo &SettingsBTData::GetSelectedBTInfo()
{
    return m_selectedBTInfo;
}

