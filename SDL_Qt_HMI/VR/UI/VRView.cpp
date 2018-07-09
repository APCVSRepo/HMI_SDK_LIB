#include "VRView.h"
#include "VR/app/VR.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/AppConfig.h"

VRView::VRView(QWidget *parent)
    :QWidget(parent)
    ,CView(VoiceRecognition::eViewId_Main)
    ,m_pTitleLab(NULL)
    ,m_pTopLine(NULL)
    ,m_pBottomLine(NULL)
    ,m_pRotate(NULL)
    ,m_pVRBtn(NULL)
    ,m_pVlist(NULL)
{
    this->setGeometry(0,0,800,480);

    m_pTopLine = new QLabel(this);
    m_pTopLine->setGeometry(97,111,607,1);
    m_pTopLine->setPixmap(QPixmap(QString(":/SDLApps/Source/images/partingline.png")));
    m_pBottomLine = new QLabel(this);
    m_pBottomLine->setGeometry(97,346,607,1);
    m_pBottomLine->setPixmap(QPixmap(QString(":/SDLApps/Source/images/partingline.png")));

    m_pTitleLab = new QLabel(this);
    m_pTitleLab->setStyleSheet("font: 30px;color:rgb(75,169,255)");
    m_pTitleLab->setGeometry(168,62,465,41);
    m_pTitleLab->setAlignment(Qt::AlignCenter);
    m_pTitleLab->setText(QString(tr("Hello: what can I do for you")));

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
    m_pVlist->setGeometry(180,112,800-180-180,234);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->setEnabled(false);
    m_pVlist->show();

    //help info
    {
        CListWidgetItem item (QSize(800-180-180,53));
        item.AddText(QRect(0,15,600,33),QString(tr("You can say this:")),Qt::AlignLeft|Qt::AlignVCenter,24);
        m_pVlist->InsertItem(m_pVlist->count(),item);
    }
    {
        CListWidgetItem item (QSize(800-180-180,86));
                item.AddIcon(QRect(0,19,40,40),QPixmap(":/VR/Source/images/phone_icon.png"));
                item.AddText(QRect(62,17,378,19),QString(tr("Phone")),Qt::AlignLeft|Qt::AlignVCenter,18,QColor(128,128,128));
                item.AddText(QRect(62,17+29,378,19),QString(tr("\"Call 10080.\"")),Qt::AlignLeft|Qt::AlignVCenter,18,QColor(128,128,128));
        m_pVlist->InsertItem(m_pVlist->count(),item);
    }
    {
        CListWidgetItem item (QSize(800-180-180,86));
        item.AddIcon(QRect(0,19,40,40),QPixmap(":/VR/Source/images/message_icon.png"));
        item.AddText(QRect(62,17,378,19),QString(tr("Messages")),Qt::AlignLeft|Qt::AlignVCenter,18,QColor(128,128,128));
        item.AddText(QRect(62,17+29,378,19),QString(tr("\"Texti586.\"")),Qt::AlignLeft|Qt::AlignVCenter,18,QColor(128,128,128));
        m_pVlist->InsertItem(m_pVlist->count(),item);
    }
}

VRView::~VRView()
{

}

void VRView::viewAction(int state)
{
    INFO("VRView  viewAction state = %d", state);
    if(eviewStatus_Init == state)
    {

    }
    else if(eViewStatus_Inactive == state)
    {

    }
    else
    {
        INFO("VRView::viewAction eViewStatus_Active");
    }
}

void VRView::showEvent(QShowEvent *)
{
    m_pRotate->start();
}

void VRView::hideEvent(QHideEvent *)
{
    m_pRotate->stop();
}

void VRView::OnVRBtnClicked()
{
    VoiceRecognition::Inst()->ViewForwardById(VoiceRecognition::eViewId_Interaction);
}
