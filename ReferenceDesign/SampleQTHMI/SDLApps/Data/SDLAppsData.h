#ifndef SDLAPPSDATA_H
#define SDLAPPSDATA_H

#include <QObject>

struct SDLAppInfo{
    SDLAppInfo(int id, std::string name, std::string icon, std::string type)
        :appId(id)
        ,appName(name)
        ,appIcon(icon)
        ,appType(type)
    {

    }

    int appId;
    std::string appName;
    std::string appIcon;
    std::string appType;
};

class SDLAppsData : public QObject
{
    Q_OBJECT
public:
    static SDLAppsData *GetInstance();

//    void AppRegister(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes);
    void UpdateAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes);
//    void AppUnRegister(int id);
    std::vector<SDLAppInfo> GetNavigationAppList();
    std::vector<SDLAppInfo> GetMediaAppList();

private:
    void PrintAppList();

private:
    explicit SDLAppsData(QObject *parent = 0);

signals:

public slots:


private:

    std::vector<SDLAppInfo> m_vAppInfos;




private:
    static SDLAppsData *s_pInstance;
};

#endif // SDLAPPSDATA_H
