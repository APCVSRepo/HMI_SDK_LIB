#include "VRInteractionView.h"
#include "VR/app/VR.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/AppConfig.h"

VRInteractionView::VRInteractionView(QWidget *parent)
    :QWidget(parent)
    ,CView(VR::eViewId_Interaction)
    ,m_pRotate(NULL)
    ,m_pVRBtn(NULL)
    ,m_pVlist(NULL)
{
    this->setGeometry(0,0,800,480);

    //vr button
    m_pRotate = new CRotationWidget(this);
    m_pRotate->setPixmap(QPixmap(QString(":/SDLApps/Source/images/vr_light.png")));
    m_pRotate->setGeometry(364,372,73,73);
    m_pRotate->show();

    m_pVRBtn = new CPushButton(this);
    m_pVRBtn->setGeometry(364+7,372+7,59,59);
    m_pVRBtn->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/vr_microphone.png);background:transparent;}");
    m_pVRBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pVRBtn, SIGNAL(clicked()), this, SLOT(OnVRBtnClicked()));

    //list
    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,40,800-54-54,346-60);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/VR/Source/images/partingline.png",":/VR/Source/images/partingline.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->AutoSetSelected(false);
    m_pVlist->show();

    //test data
    {
        CListWidgetItem item (QSize(800-54-54,90));
        item.AddIcon(QRect(0,20,50,50),QPixmap(":/VR/Source/images/vr.png"));
        item.AddText(QRect(121-54,28,380,33),QString(tr("Hello: what can I do for you")),Qt::AlignLeft|Qt::AlignVCenter,24);
        m_pVlist->InsertItem(m_pVlist->count(),item);
    }
    {
        CListWidgetItem item (QSize(800-54-54,90));
                item.AddIcon(QRect(696-54,20,50,50),QPixmap(":/VR/Source/images/vr_peple.png"));
                item.AddText(QRect(299-54,28,380,33),QString(tr("\"call 10080.\"")),Qt::AlignRight|Qt::AlignVCenter,24);
        m_pVlist->InsertItem(m_pVlist->count(),item);
    }
    {
        CListWidgetItem item (QSize(800-54-54,90));
        item.AddIcon(QRect(0,20,50,50),QPixmap(":/VR/Source/images/vr.png"));
        item.AddText(QRect(121-54,28,380,33),QString(tr("Call 10086.")),Qt::AlignLeft|Qt::AlignVCenter,24);
        m_pVlist->InsertItem(m_pVlist->count(),item);
    }
}

VRInteractionView::~VRInteractionView()
{

}

void VRInteractionView::viewAction(int state)
{
    INFO("VRInteractionView  viewAction state = %d", state);
    if(eviewStatus_Init == state)
    {

    }
    else if(eViewStatus_Inactive == state)
    {

    }
    else
    {
        INFO("VRInteractionView::viewAction eViewStatus_Active");
    }
}

void VRInteractionView::showEvent(QShowEvent *)
{
    m_pRotate->start();
}

void VRInteractionView::hideEvent(QHideEvent *)
{
    m_pRotate->stop();
}

void VRInteractionView::OnVRBtnClicked()
{
    //TODO:
}
