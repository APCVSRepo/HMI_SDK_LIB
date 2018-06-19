#include "SliderView.h"
#include <QBoxLayout>

CSliderView::CSliderView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_bDynamic(false)
    ,m_pHeaderLab(NULL)
    ,m_pFooterLab(NULL)
    ,m_pSlider(NULL)
    ,m_pTopWidget(NULL)
    ,m_pSaveBtn(NULL)
    ,m_pReturnBtn(NULL)
    ,m_pTimer(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //slider
    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    m_pHeaderLab = new QLabel;
    m_pFooterLab = new QLabel;
    m_pSlider = new QSlider(Qt::Horizontal);

    pMainLayout->addWidget(m_pHeaderLab, 0, Qt::AlignCenter);
    pMainLayout->addWidget(m_pSlider);
    pMainLayout->addWidget(m_pFooterLab, 0, Qt::AlignCenter);
    pMainLayout->setContentsMargins(54, 70, 54, 70);

    m_pHeaderLab->setStyleSheet("font: 36px;color:rgb(255,255,255)");
    m_pFooterLab->setStyleSheet("font: 36px;color:rgb(255,255,255)");

    m_pSlider->setStyleSheet("QSlider{height:36px;background:transparent}"
                             "QSlider::groove{margin:10px 0;background:rgb(100,109,119)}"
                             "QSlider::handle{width:21px;margin:-10px 0;border-image:url(:images/slider_handle.png)}");

    connect(m_pSlider, SIGNAL(valueChanged(int)), SLOT(OnSliderValueChanged(int)));

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowBack();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(OnReturnBtnClicked()));

    //button
    m_pSaveBtn = new QPushButton(this);
    m_pSaveBtn->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/Settings/button_a.png);}"
                              "QPushButton:pressed{color:#66ffffff;background-image:url(:/Settings/button_a.png);border:none;}");
    m_pSaveBtn->setGeometry(229,356,131,32);
    m_pSaveBtn->setFocusPolicy(Qt::NoFocus);
    m_pSaveBtn->setText(QString(tr("Save")));

    m_pReturnBtn = new QPushButton(this);
    m_pReturnBtn->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/Settings/button_a.png);}"
                                "QPushButton:pressed{color:#66ffffff;background-image:url(:/Settings/button_a.png);border:none;}");
    m_pReturnBtn->setGeometry(440,356,131,32);
    m_pReturnBtn->setFocusPolicy(Qt::NoFocus);
    m_pReturnBtn->setText(QString(tr("Return")));

    connect(m_pSaveBtn, SIGNAL(clicked()), this, SLOT(OnSaveBtnClicked()));
    connect(m_pReturnBtn, SIGNAL(clicked()), this, SLOT(OnReturnBtnClicked()));

    //timer
    m_pTimer = new QTimer;
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimeOut()));
}

CSliderView::~CSliderView() {
    delete m_pHeaderLab;
    delete m_pFooterLab;
    delete m_pSlider;
    delete m_pTimer;
}

void CSliderView::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    if (AppControl) {
        m_pTopWidget->SetTitle(QString::fromStdString(AppControl->getAppName()));

        rpcValueInterface &m_jsonData = AppControl->getSlider();

        m_pTimer->start(m_jsonData["params"]["timeout"].asInt());

        int numTicks = m_jsonData["params"]["numTicks"].asInt();
        int position = m_jsonData["params"]["position"].asInt();

        AppBase::SetEdlidedText(m_pHeaderLab,
                                m_jsonData["params"]["sliderHeader"].asString().c_str(),
                width() * 0.9);

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

void CSliderView::UpdateFooter(int iPos) {
    // Bug #9938
    if (m_FooterStrVec.size() < 1)
        return;

    if (m_bDynamic) {
        AppBase::SetEdlidedText(m_pFooterLab, m_FooterStrVec[iPos - 1].c_str(), width() * 0.9);
    } else {
        AppBase::SetEdlidedText(m_pFooterLab, m_FooterStrVec[0].c_str(), width() * 0.9);
    }
}

void CSliderView::OnSliderValueChanged(int iValue) {
    UpdateFooter(iValue);
}

void CSliderView::OnTimeOut() {
    m_pTimer->stop();
    AppControl->OnSliderResponse(RESULT_TIMED_OUT, m_pSlider->value());
}

void CSliderView::OnSaveBtnClicked()
{
    m_pTimer->stop();
    AppControl->OnSliderResponse(RESULT_SUCCESS, m_pSlider->value());
}

void CSliderView::OnReturnBtnClicked() {
    m_pTimer->stop();
    AppControl->OnSliderResponse(RESULT_ABORTED, m_pSlider->value());
}
