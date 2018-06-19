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
    ,m_BTStatus("Close")
{
    BTDeviceInfo info1;
    info1.id = 1;
    info1.name = "JBL";
    info1.status = BTStatus_PAIRED;
    info1.address = "01:01:01:01:01:01";
    info1.pin = 1111;
    info1.password = "123456";
    m_BTPairedList.push_back(info1);

    BTDeviceInfo info2;
    info2.id = 2;
    info2.name = "HUAWEI";
    info2.status = BTStatus_PAIRED;
    info2.address = "01:01:01:01:01:01";
    info2.pin = 0001;
    info2.password = "222222";
    m_BTPairedList.push_back(info2);

    BTDeviceInfo info3;
    info3.id = 3;
    info3.name = "XiaoMi 3333";
    info3.status = BTStatus_PAIRED;
    info3.address = "01:01:01:01:01:01";
    info3.pin = 3333;
    info3.password = "333333";
    m_BTPairedList.push_back(info3);

    BTDeviceInfo info4;
    info4.id = 4;
    info4.name = "Nokia 4444";
    info4.status = BTStatus_PAIRED;
    info4.address = "01:01:01:01:01:01";
    info4.pin = 4444;
    info4.password = "444444";
    m_BTPairedList.push_back(info4);

    BTDeviceInfo info5;
    info5.id = 5;
    info5.name = "JBL_555555";
    info5.status = BTStatus_NORMAL;
    info5.address = "01:01:01:01:01:01";
    info5.pin = 1234;
    info5.password = "555555";
    m_BTSearchList.push_back(info5);

    BTDeviceInfo info6;
    info6.id = 6;
    info6.name = "JBL6666";
    info6.status = BTStatus_NORMAL;
    info6.address = "01:01:01:01:01:01";
    info6.pin = 6666;
    info6.password = "666666";
    m_BTSearchList.push_back(info6);

    BTDeviceInfo info7;
    info7.id = 7;
    info7.name = "JBL7777";
    info7.status = BTStatus_NORMAL;
    info7.address = "01:01:01:01:01:01";
    info7.pin = 7777;
    info7.password = "777777";
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

void SettingsBTData::ConnectDevice(int id)
{
    bool bFindInPairedList = false;
    for(int i = 0; i < m_BTPairedList.size(); ++i)
    {
        if(id == m_BTPairedList[i].id)
        {
            m_BTPairedList[i].status = BTStatus_CONNECTED;
            bFindInPairedList = true;
        }
        else
        {
            m_BTPairedList[i].status = BTStatus_PAIRED;
        }
    }
    if(bFindInPairedList)
    {
        emit deviceListUpdate();
        return;
    }

    vector<BTDeviceInfo>::iterator iter = m_BTSearchList.begin();
    int i = 0;
    for(iter; iter != m_BTSearchList.end(); ++iter)
    {
        if(id == iter->id)
        {
            BTDeviceInfo info = m_BTSearchList[i];
            m_BTSearchList.erase(iter);

            info.status = BTStatus_CONNECTED;
            m_BTPairedList.push_back(info);
            emit deviceListUpdate();

            return;
        }
        ++i;
    }
}

void SettingsBTData::DisconnectDevice(int id)
{
    for(int i = 0; i < m_BTPairedList.size(); ++i)
    {
        if(id == m_BTPairedList[i].id)
        {
            m_BTPairedList[i].status = BTStatus_PAIRED;
            emit deviceListUpdate();
            return;
        }
    }
}

void SettingsBTData::RemoveDeviceFromPairedList(int id)
{
    vector<BTDeviceInfo>::iterator iter = m_BTPairedList.begin();
    int i = 0;
    for(iter; iter != m_BTPairedList.end(); ++iter)
    {
        if(id == iter->id)
        {
            BTDeviceInfo info = m_BTPairedList[i];
            m_BTPairedList.erase(iter);

            info.status = BTStatus_NORMAL;
            m_BTSearchList.push_back(info);
            emit deviceListUpdate();

            return;
        }
        ++i;
    }
}

void SettingsBTData::OnBTStatusChanged(int status)
{
    if(status)
    {
        m_BTStatus = QString("Open");
    }
    else
    {
        m_BTStatus = QString("Close");
    }
    emit BTStatusChanged(m_BTStatus);
}

