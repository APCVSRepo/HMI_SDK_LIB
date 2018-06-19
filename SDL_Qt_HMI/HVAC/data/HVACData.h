#ifndef HVACDATA_H
#define HVACDATA_H

#include <QObject>

class HVACData : public QObject
{
    Q_OBJECT
    explicit HVACData();

public:
    void SetZone(int zone);

    int GetZone();
    static HVACData*Inst();

signals:
    void SigZone(int);
public slots:

private:
    static HVACData* m_pInst;
    int m_iZone;

};

#endif // HVACDATA_H
