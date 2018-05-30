#ifndef SETTINGSDATETIMEDATA_H
#define SETTINGSDATETIMEDATA_H

#include <QObject>

class SettingsDateTimeData : public QObject
{
    Q_OBJECT
    explicit SettingsDateTimeData();

public:
    void SetHour12Or24(bool bHour12Or24);
    static SettingsDateTimeData*Inst();

signals:
    void Hour12Or24Change(bool);
public slots:

private:
    static SettingsDateTimeData* m_pInst;
    bool m_bIs12Or24Hour;

};

#endif // SETTINGSDATETIMEDATA_H
