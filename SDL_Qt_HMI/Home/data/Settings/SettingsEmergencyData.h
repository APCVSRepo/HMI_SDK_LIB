#ifndef SETTINGSEMERGENCYDATA_H
#define SETTINGSEMERGENCYDATA_H
#include <QObject>

class SettingsEmergencyData : public QObject
{
    Q_OBJECT
    explicit SettingsEmergencyData();


public:
    static SettingsEmergencyData *Inst();

    void SetEmergencRescueStatus(QString status);


signals:
    void EmergencRescueStatusChange(QString);
public slots:

private:
    static SettingsEmergencyData* m_pInst;
    QString m_EmergencRescueStatus;

};

#endif // SETTINGSEMERGENCYDATA_H
