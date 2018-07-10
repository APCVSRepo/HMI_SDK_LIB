#ifndef SETTINGSROUTINESETTINGDATA_H
#define SETTINGSROUTINESETTINGDATA_H

#include <QObject>

class SettingsRoutineSettingData : public QObject
{
    Q_OBJECT
    explicit SettingsRoutineSettingData();


public:
    static SettingsRoutineSettingData *Inst();

    void SetLanguage(QString language);


signals:
    void LanguageChannge(QString);
public slots:

private:
    static SettingsRoutineSettingData* m_pInst;
    QString m_language;

};
#endif // SETTINGSROUTINESETTINGDATA_H
