#ifndef SETTINGSDISPLAYDATA_H
#define SETTINGSDISPLAYDATA_H

#include <QObject>

class SettingsDisplayData : public QObject
{
    Q_OBJECT
    explicit SettingsDisplayData();


public:
    static SettingsDisplayData *Inst();

    void SetPattern(QString pattern);


signals:
    void PatternChannge(QString);
public slots:

private:
    static SettingsDisplayData* m_pInst;
    QString m_pattern;

};

#endif // SETTINGSDISPLAYDATA_H
