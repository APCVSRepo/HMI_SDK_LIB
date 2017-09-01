#include "ChoiceSetVR.h"
#include <QBoxLayout>
#include "Common/AppBase.h"

CChoiceSetVR::CChoiceSetVR(QWidget *parent) :
    QWidget(parent)
{
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
    }
    //m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/choicevr_back.png");
    pixmap = pixmap.scaled(width(),height(), Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);

    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    QHBoxLayout *pCmdLayout = new QHBoxLayout;
    m_pTitleLab = new QLabel;

    pMainLayout->addWidget(m_pTitleLab);
    for (int i = 0;i != 4;++i) {
        pMainLayout->addWidget(m_aChoiceLab+i);
        m_aChoiceLab[i].setStyleSheet("font: 30px \"Liberation Serif\";color:rgb(0,0,0)");
        m_aChoiceLab[i].setAlignment(Qt::AlignCenter);
    }
    pMainLayout->addLayout(pCmdLayout);
    pMainLayout->setContentsMargins(20,20,20,20);

    for (int i = 0;i != 3;++i) {
        pCmdLayout->addWidget(m_aCmdLab+i,1);
        m_aCmdLab[i].setStyleSheet("font: 30px \"Liberation Serif\";color:rgb(0,0,0)");
        m_aCmdLab[i].setAlignment(Qt::AlignCenter);
    }

    QString strCmdText[3] = {"帮助","","返回"};
    m_aCmdLab[0].setText(strCmdText[0]);
    m_aCmdLab[2].setText(strCmdText[2]);

    m_pTitleLab->setStyleSheet("border-image:url(:/images/choicevr_title.png);font: 30px \"Liberation Serif\";color:rgb(255,255,255)");
    m_pTitleLab->setMinimumHeight(width()*0.08);
    m_pTitleLab->setAlignment(Qt::AlignCenter);
}

CChoiceSetVR::~CChoiceSetVR()
{
    delete m_pTitleLab;
}

void CChoiceSetVR::mousePressEvent(QMouseEvent * event)
{
    emit pressed();
}

void CChoiceSetVR::SetTitle(std::string strTitle)
{
    AppBase::SetEdlidedText(m_pTitleLab,strTitle.c_str(),width()*0.7);
}

void CChoiceSetVR::SetChoice(int iPos,std::string strChoice)
{
    if (iPos < 4) {
        AppBase::SetEdlidedText(m_aChoiceLab+iPos,strChoice.c_str(),width()*0.8);
    }
}
