#ifndef SETTINGSWIFIDATA_H
#define SETTINGSWIFIDATA_H

#include <QObject>
#include <QString>
//#include <string>
#include <vector>

using namespace std;

enum eSecurityType
{
    SecurityType_NONE,
    SecurityType_WEP,
    SecurityType_WPA,
    SecurityType_WPA2,
    SecurityType_WPA_WPA2
};

struct WifiDeviceInfo
{
    int id;
    QString name;
    eSecurityType securityType;
    int signalIntensity;    //1~100
    QString address;
    QString password;
    bool connected;
};

class SettingsWifiData: public QObject
{
    Q_OBJECT

public:
    static SettingsWifiData *GetInstance();

    const WifiDeviceInfo &GetWifiListInfo(int index)const;
    int GetWifiListSize()const;

    void SetSelectedWifiInfo(const WifiDeviceInfo& info);
    const WifiDeviceInfo &GetSelectedWifiInfo();

    bool CheckPassword(QString password = QString());
    bool CheckPasswordWithWifiInfo(QString netName, QString securityType, QString password);

signals:
    void SigWifiListUpdate();

private:
    SettingsWifiData(QObject *parent=0);
    void ConnectToWifi(int id);

private:
    vector<WifiDeviceInfo> m_wifiList;
    WifiDeviceInfo m_selectedWifiInfo;

    static SettingsWifiData *s_pInstance;
};

#endif // SETTINGSWIFIDATA_H
