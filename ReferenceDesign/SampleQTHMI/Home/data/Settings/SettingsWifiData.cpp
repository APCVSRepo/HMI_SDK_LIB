#include "SettingsWifiData.h"
#include "HMIFrameWork/log_interface.h"

SettingsWifiData *SettingsWifiData::s_pInstance = NULL;

SettingsWifiData *SettingsWifiData::GetInstance()
{
    if(NULL == s_pInstance)
    {
        s_pInstance = new SettingsWifiData;
    }
    return s_pInstance;
}

SettingsWifiData::SettingsWifiData(QObject *parent)
    :QObject(parent)
    ,m_WifiStatus("Close")
{
    WifiDeviceInfo info1;
    info1.id = 1;
    info1.name = "TP-Link_1234";
    info1.securityType = SecurityType_WPA_WPA2;
    info1.signalIntensity = 100;
    info1.address = "01:01:01:01:01:01";
    info1.password = "1234";
    info1.connected = false;
    m_wifiList.push_back(info1);

    WifiDeviceInfo info2;
    info2.id = 2;
    info2.name = "TP-Link_2345";
    info2.securityType = SecurityType_NONE;
    info2.signalIntensity = 90;
    info2.address = "02:02:02:02:02:02";
    info2.password = "";
    info2.connected = false;
    m_wifiList.push_back(info2);

    WifiDeviceInfo info3;
    info3.id = 3;
    info3.name = "TP-Link_3333";
    info3.securityType = SecurityType_WPA;
    info3.signalIntensity = 80;
    info3.address = "03:03:03:03:03:03";
    info3.password = "3333";
    info3.connected = false;
    m_wifiList.push_back(info3);

    WifiDeviceInfo info4;
    info4.id = 4;
    info4.name = "TP-Link_4444";
    info4.securityType = SecurityType_WPA2;
    info4.signalIntensity = 40;
    info4.address = "04:04:04:04:04:04";
    info4.password = "4444";
    info4.connected = false;
    m_wifiList.push_back(info4);

    WifiDeviceInfo info5;
    info5.id = 5;
    info5.name = "TP-Link_VeryLong1234567890123456789012345678901234567890";
    info5.securityType = SecurityType_WEP;
    info5.signalIntensity = 60;
    info5.address = "AB:AB:AB:AB:AB:AB";
    info5.password = "1234567890";
    info5.connected = false;
    m_wifiList.push_back(info5);
}

void SettingsWifiData::ConnectToWifi(int id)
{
    for(vector<WifiDeviceInfo>::iterator iter = m_wifiList.begin(); iter!=m_wifiList.end(); ++iter)
    {
        if(true == (*iter).connected)
        {
            (*iter).connected = false;
            break;
        }
    }

    for(vector<WifiDeviceInfo>::iterator iter = m_wifiList.begin(); iter!=m_wifiList.end(); ++iter)
    {
        if(id == (*iter).id)
        {
            (*iter).connected = true;
            break;
        }
    }

    emit SigWifiListUpdate();
}

const WifiDeviceInfo &SettingsWifiData::GetWifiListInfo(int index) const
{
    return m_wifiList[index];
}

int SettingsWifiData::GetWifiListSize() const
{
    return m_wifiList.size();
}

void SettingsWifiData::SetSelectedWifiInfo(const WifiDeviceInfo &info)
{
    m_selectedWifiInfo = info;
}

const WifiDeviceInfo &SettingsWifiData::GetSelectedWifiInfo()
{
    return m_selectedWifiInfo;
}

bool SettingsWifiData::CheckPassword(QString password)
{
    if(m_selectedWifiInfo.password == password)
    {
        ConnectToWifi(m_selectedWifiInfo.id);
        return true;
    }
    else
    {
        return false;
    }
}

bool SettingsWifiData::CheckPasswordWithWifiInfo(QString netName, QString securityType, QString password)
{
    INFO("CheckPasswordWithWifiInfo: netName is %s , securityType is %s , password is %s",netName.toStdString().c_str(),securityType.toStdString().c_str(),password.toStdString().c_str());
    if("123456" == netName  && "WPA/WPA2" == securityType && "123456" == password )
    {
        WifiDeviceInfo info;
        info.id = 6;
        info.name = "123456";
        info.securityType = SecurityType_WPA_WPA2;
        info.signalIntensity = 60;
        info.address = "12:34:56:12:34:56";
        info.password = "123456";
        m_wifiList.push_back(info);

        ConnectToWifi(info.id);
        return true;
    }
    else
    {
        return false;
    }
}

void SettingsWifiData::OnWifiStatusChanged(int status)
{
    if(status)
    {
        m_WifiStatus = QString("Open");
    }
    else
    {
        m_WifiStatus = QString("Close");
    }
    emit WifiStatusChanged(m_WifiStatus);
}
