#include "ChoiceSetVR.h"
#include <QBoxLayout>
#include "SDLApps/Templates/Common/AppBase.h"

CChoiceSetVR::CChoiceSetVR(QWidget *parent)
    :QWidget(parent)
    ,m_pTitleLab(NULL)
    ,m_pTopLine(NULL)
    ,m_pBottomLine(NULL)
    ,m_pChoiceArea(NULL)
    ,m_pRotate(NULL)
    ,m_pVRBtn(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    m_pTopLine = new QLabel(this);
    m_pTopLine->setGeometry(97,111-40,607,1);
    m_pTopLine->setPixmap(QPixmap(QString(":/SDLApps/Source/images/partingline.png")));
    m_pBottomLine = new QLabel(this);
    m_pBottomLine->setGeometry(97,346-40,607,1);
    m_pBottomLine->setPixmap(QPixmap(QString(":/SDLApps/Source/images/partingline.png")));

    m_pTitleLab = new QLabel(this);
    m_pTitleLab->setStyleSheet("font: 30px;color:rgb(75,169,255)");
    m_pTitleLab->setGeometry(168,62-40,465,41);
    m_pTitleLab->setAlignment(Qt::AlignCenter);

    //cmd
    m_pChoiceArea = new QWidget(this);
    m_pChoiceArea->setGeometry(168,112-40,800-168-168,234);

    for (int i = 0; i != 4; ++i) {
        m_aChoiceLab[i].setParent(m_pChoiceArea);
        m_aChoiceLab[i].setGeometry(0,57*i,800-168-168, 57);
        m_aChoiceLab[i].setStyleSheet("font: 24px;color:rgb(255,255,255)");
        m_aChoiceLab[i].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }

    //vr button
    m_pRotate = new CRotationWidget(this);
    m_pRotate->setPixmap(QPixmap(QString(":/SDLApps/Source/images/vr_light.png")));
    m_pRotate->setGeometry(364,372-40,73,73);
    m_pRotate->show();

    m_pVRBtn = new CPushButton(this);
    m_pVRBtn->setGeometry(364+7,372-40+7,59,59);
    m_pVRBtn->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/vr_microphone.png);background:transparent;}");
    m_pVRBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pVRBtn, SIGNAL(clicked()), this, SLOT(OnVRBtnClicked()));
}

CChoiceSetVR::~CChoiceSetVR() {
    delete m_pTitleLab;
}

void CChoiceSetVR::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit pressed();
}

void CChoiceSetVR::OnVRBtnClicked()
{
    //TODO: send vr cmd??? currently do nothing, just hide the view
    emit released();
}

void CChoiceSetVR::showEvent(QShowEvent *)
{
    m_pRotate->start();
}

void CChoiceSetVR::hideEvent(QHideEvent *)
{
    m_pRotate->stop();
}

void CChoiceSetVR::SetTitle(std::string strTitle) {
    AppBase::SetEdlidedText(m_pTitleLab, strTitle.c_str(), 800-168-168, Qt::AlignCenter);
}

void CChoiceSetVR::SetChoice(int iPos, std::string strChoice) {
    if (iPos < 4) {
        QLabel *pLabel = m_aChoiceLab + iPos;
        QFontMetrics qfm(pLabel->font());
        pLabel->setText(qfm.elidedText(QString::fromStdString(strChoice), Qt::ElideRight, 800-168-168));
    }
}

void CChoiceSetVR::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit released();
}
