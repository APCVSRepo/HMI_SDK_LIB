#include "BootAnimation.h"
#include <QVBoxLayout>
#include <QFile>
BootAnimation::BootAnimation(QWidget *parent)
    :QWidget(parent)
{
    this->setGeometry(QRect(0,0,800,480));
    m_player.RegisterMessageCallback(dynamic_cast<GstPlayerMessage*>(this));
    m_player.open("Main_build_3.mov","ximagesink",true,this->winId());

}

BootAnimation::~BootAnimation()
{

}

void BootAnimation::OnGstPlayerStatus(eGstPlayerStatus status)
{
    if(status == eGstPlayer_Finish)
    {
        emit PlayFinish();
    }
}

void BootAnimation::PlayAnimation()
{
    m_player.play();
}

void BootAnimation::Stop()
{
    m_player.stop();
}
