#ifndef BOOTANIMATION_H
#define BOOTANIMATION_H
#include <QWidget>
#include <stdio.h>
#include "HMIFrameWork/GstPlayer.h"
#include "HMIFrameWork/GstPlayerMessage.h"
class BootAnimation:public QWidget,public GstPlayerMessage
{
    Q_OBJECT
public:
    explicit BootAnimation(QWidget* parent = 0);
    ~BootAnimation();
    virtual void OnGstPlayerStatus(eGstPlayerStatus status);

    void PlayAnimation();
    void Stop();
public :signals:
    void PlayFinish();
private:
    CGstPlayer m_player;
};

#endif // BOOTANIMATION_H
