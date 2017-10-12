#include "SliderView.h"
#include <QBoxLayout>

CSliderView::CSliderView(AppListInterface * pList, QWidget *parent)
    : QWidget(parent),
    m_bDynamic(false)
{
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
    }
    m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/MainWidget/Backgroud.png");
    pixmap = pixmap.scaled(width(),height(), Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);

    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    QHBoxLayout *pTopLayout = new QHBoxLayout;
    QHBoxLayout *pBottomLayout = new QHBoxLayout;
    m_pAppNameLab = new QLabel;
    m_pHeaderLab = new QLabel;
    m_pFooterLab = new QLabel;
    m_pSlider = new QSlider(Qt::Horizontal);
    m_pReturnBtn = new CCustomButton;

    pMainLayout->addLayout(pTopLayout);
    pMainLayout->addWidget(m_pHeaderLab);
    pMainLayout->addWidget(m_pSlider);
    pMainLayout->addWidget(m_pFooterLab);
    pMainLayout->addLayout(pBottomLayout);
    pMainLayout->setContentsMargins(height()*0.04,height()*0.04,
                                    height()*0.04,height()*0.1);

    pTopLayout->addWidget(m_pReturnBtn);
    pTopLayout->addWidget(m_pAppNameLab,1);

    pBottomLayout->addStretch(1);
    for (int i = 0;i != 2;++i) {
        pBottomLayout->addWidget(m_aSoftBtn + i);        
        m_aSoftBtn[i].SetTextStyle("font: 32px \"Liberation Serif\";color:rgb(0,0,0)");
        m_aSoftBtn[i].SetId(i);
        connect(m_aSoftBtn + i,SIGNAL(Clicked(int)),this,SLOT(OnSoftBtnClicked(int)));
    }
    m_aSoftBtn[0].Init(width()*0.22,width()*0.07,"保存",":/images/alert_softbtn_normal.png",":/images/alert_softbtn_press.png");
    m_aSoftBtn[1].Init(width()*0.22,width()*0.07,"返回",":/images/alert_softbtn_normal.png",":/images/alert_softbtn_press.png");
    pBottomLayout->addStretch(1);
    pBottomLayout->setSpacing(width()*0.025);

    m_pReturnBtn->Init(width()*0.07,width()*0.065,"",":/images/ReturnBtnNormal.png",":/images/ReturnBtnPress.png");
    m_pAppNameLab->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pHeaderLab->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pFooterLab->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pHeaderLab->setAlignment(Qt::AlignCenter);
    m_pFooterLab->setAlignment(Qt::AlignCenter);

    m_pSlider->setStyleSheet("QSlider{height:36px;background:transparent}\
                             QSlider::groove{margin:10px 0;background:rgb(100,109,119)}\
                             QSlider::handle{width:21px;margin:-10px 0;border-image:url(:images/slider_handle.png)\
                             }");

    connect(m_pSlider,SIGNAL(valueChanged(int)),SLOT(OnSliderValueChanged(int)));

    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(OnTimeOut()));
    connect(m_pReturnBtn,SIGNAL(Clicked()),SLOT(OnReturnBtnClicked()));
}

CSliderView::~CSliderView()
{
    delete m_pAppNameLab;
    delete m_pHeaderLab;
    delete m_pFooterLab;
    delete m_pSlider;
    delete m_pReturnBtn;
    delete m_pTimer;
}

void CSliderView::OnSoftBtnClicked(int iSoftBtnID)
{
    if (iSoftBtnID == 0) {
        m_pTimer->stop();
        AppControl->OnSliderResponse(RESULT_SUCCESS,m_pSlider->value());
    } else if (iSoftBtnID == 1) {
        m_pTimer->stop();
        AppControl->OnSliderResponse(RESULT_ABORTED,m_pSlider->value());
    }
}

void CSliderView::showEvent(QShowEvent * e)
{
    Q_UNUSED(e);
    if (AppControl) {
        AppBase::SetEdlidedText(m_pAppNameLab,AppControl->getAppName().c_str(),width()*0.9);

        rpcValueInterface& m_jsonData = AppControl->getSlider();

        m_pTimer->start(m_jsonData["params"]["timeout"].asInt());

        int numTicks = m_jsonData["params"]["numTicks"].asInt();
        int position = m_jsonData["params"]["position"].asInt();

        AppBase::SetEdlidedText(m_pHeaderLab,
                m_jsonData["params"]["sliderHeader"].asString().c_str(),
                width()*0.9);

        m_FooterStrVec.clear();
        if (m_jsonData["params"].isMember("sliderFooter")) {
            if (m_jsonData["params"]["sliderFooter"].size() == 1) {
                m_bDynamic = false;
            } else {
                m_bDynamic = true;
            }
            for (unsigned int i = 0; i < m_jsonData["params"]["sliderFooter"].size(); ++i) {
                m_FooterStrVec.push_back(m_jsonData["params"]["sliderFooter"][i].asString());
            }
        }
        m_pSlider->setMinimum(1);
        m_pSlider->setMaximum(numTicks);
        m_pSlider->setValue(position);
        UpdateFooter(position);
    }
}

void CSliderView::UpdateFooter(int iPos)
{
    // Bug #9938
    if(m_FooterStrVec.size() < 1)
        return;

    if (m_bDynamic) {
        AppBase::SetEdlidedText(m_pFooterLab,m_FooterStrVec[iPos-1].c_str(),width()*0.9);
    } else {
        AppBase::SetEdlidedText(m_pFooterLab,m_FooterStrVec[0].c_str(),width()*0.9);
    }
}

void CSliderView::OnSliderValueChanged(int iValue)
{
    UpdateFooter(iValue);
}

void CSliderView::OnTimeOut()
{
    m_pTimer->stop();
    AppControl->OnSliderResponse(RESULT_TIMED_OUT,m_pSlider->value());
}

void CSliderView::OnReturnBtnClicked()
{
    m_pTimer->stop();
    AppControl->OnSliderResponse(RESULT_ABORTED,m_pSlider->value());
}
