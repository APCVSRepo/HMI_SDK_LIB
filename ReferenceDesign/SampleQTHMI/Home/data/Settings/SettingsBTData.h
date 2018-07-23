#ifndef SETTINGSBTDATA_H
#define SETTINGSBTDATA_H

#include <QObject>
#include <QString>
//#include <string>
#include <vector>

using namespace std;

//enum eSecurityType
//{
//    SecurityType_NONE,
//    SecurityType_WEP,
//    SecurityType_WPA,
//    SecurityType_WPA2,
//    SecurityType_WPA_WPA2
//};

enum eBTStatus
{
    BTStatus_NORMAL,
    BTStatus_PAIRED,
    BTStatus_CONNECTING,
    BTStatus_CONNECTED
};

struct BTDeviceInfo
{
    int id;
    QString name;
    eBTStatus status;
//    eSecurityType securityType;
//    int signalIntensity;    //1~100
    QString address;
    int pin;
    QString password;
//    bool connected;
};

class SettingsBTData: public QObject
{
    Q_OBJECT

public:
    static SettingsBTData *GetInstance();

    const BTDeviceInfo &GetBTPairedListInfo(int index)const;
    int GetBTPairedListSize()const;

    const BTDeviceInfo &GetBTSearchListInfo(int index)const;
    int GetBTSearchListSize()const;

    void SetSelectedBTInfo(const BTDeviceInfo& info);
    const BTDeviceInfo &GetSelectedBTInfo();

    void ConnectDevice(int id);
    void DisconnectDevice(int id);
    void RemoveDeviceFromPairedList(int id);

signals:
    void deviceListUpdate();
    void BTStatusChanged(QString status);

public slots:
    void OnBTStatusChanged(int status);

private:
    SettingsBTData(QObject *parent=0);

private:
    vector<BTDeviceInfo> m_BTPairedList;
    vector<BTDeviceInfo> m_BTSearchList;
    BTDeviceInfo m_selectedBTInfo;
    QString m_BTStatus;

    static SettingsBTData *s_pInstance;
};

#endif // SETTINGSBTDATA_H
