#ifndef SETTINGSMOBILEAPPLICATIONSDATA_H
#define SETTINGSMOBILEAPPLICATIONSDATA_H

#include <QObject>

class SettingsMobileApplicationsData : public QObject
{
    Q_OBJECT
    explicit SettingsMobileApplicationsData();


public:
    static SettingsMobileApplicationsData *Inst();

    void SetMobileApplicationsStatus(QString status);


signals:
    void MobileApplicationsStatusChange(QString);
public slots:

private:
    static SettingsMobileApplicationsData* m_pInst;
    QString m_MobileApplicationsStatus;

};

#endif // SETTINGSMOBILEAPPLICATIONSDATA_H
