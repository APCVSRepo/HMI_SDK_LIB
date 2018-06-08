#include "PromptMessageView.h"
#include "HMIFrameWork/log_interface.h"
PromptMessageView::PromptMessageView(QWidget *parent)
    :PromptBase(parent)
    ,m_pNameLabel(NULL)
    ,m_pContentLabel(NULL)
    ,m_pTimeLabel(NULL)
    ,m_pIconLabel(NULL)
    ,m_pVoiceBtn(NULL)
    ,m_pBtnA(NULL)
    ,m_pBtnB(NULL)
{
    this->setGeometry(0,0,800,77);
    this->setStyleSheet("QWidget{background:transparet;}");
    m_pBtnA = new QPushButton(this);
    m_pBtnA->setGeometry(QRect(0,0,800,77));
    m_pBtnA->setStyleSheet("QPushButton{border-image:url(:/Prompt/Source/images/message_bg.png);background:transparent;}");
    m_pBtnA->setFocusPolicy(Qt::NoFocus);
    m_pBtnA->hide();

    m_pNameLabel = new QLabel(this);
    m_pNameLabel->setGeometry(QRect(76,11,300,35));
    m_pNameLabel->setStyleSheet("QLabel{border:transparent;background:transparent;color:rgb(48,48,48);font-size:26px;}");
    m_pNameLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pNameLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pNameLabel->show();

    m_pContentLabel = new QLabel(this);
    m_pContentLabel->setGeometry(QRect(76,46,380,29));
    m_pContentLabel->setStyleSheet("QLabel{border:none;background:transparent;color:rgba(45,45,45,204);font-size:24px;}");
    m_pContentLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pContentLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pContentLabel->show();

    m_pTimeLabel = new QLabel(this);
    m_pTimeLabel->setGeometry(QRect(380,11,76,22));
    m_pTimeLabel->setStyleSheet("QLabel{border:none;background:transparent;color:rgb(141,141,141);font-size:18px;}");
    m_pTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_pTimeLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pTimeLabel->show();

    m_pIconLabel = new QLabel(this);
    m_pIconLabel->setGeometry(QRect(11,11,53,48));
    m_pIconLabel->setStyleSheet("QLabel{border-image:url(:/Prompt/Source/images/message_icon.png);background:transparent;color:rgb(141,141,141);font-size:18px;}");
    m_pIconLabel->show();

    m_pBtnB = new CPushButton(this);
    m_pBtnB->setStyleSheet("QPushButton{font-size:20px;color:rgb(255,255,255);border-image:url(:/Prompt/Source/images/message_btn_bg_normal.png);background:transparent;}");
    m_pBtnB->setGeometry(687,19,94,39);
    m_pBtnB->setFocusPolicy(Qt::NoFocus);
    m_pBtnB->setText(QString(tr("Ignore")));
    m_pBtnB->hide();




    connect(m_pBtnA,SIGNAL(clicked()),this,SLOT(OnButtonA()),Qt::UniqueConnection);
    connect(m_pBtnB,SIGNAL(clicked()),this,SLOT(OnButtonA()),Qt::UniqueConnection);
}

PromptMessageView::~PromptMessageView()
{

}

void PromptMessageView::AddTitle(const QString &title)
{

}

void PromptMessageView::AddContextA(const QString &text)
{

}

void PromptMessageView::AddContextALight(const QString &text)
{

}

void PromptMessageView::AddContextB(const QString &text)
{

}

void PromptMessageView::AddContextBLight(const QString &text)
{

}

void PromptMessageView::AddBtnA(const QString &text)
{
    m_pBtnA->setText(text);
    m_pBtnA->lower();
    m_pBtnA->show();
}

void PromptMessageView::AddBtnB(const QString &text)
{
    m_pBtnB->setText(text);
    m_pBtnB->show();
}

void PromptMessageView::AddTimer(int time)
{
    m_timer.setInterval(time);
    m_timer.setSingleShot(true);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(OnTimer()),Qt::UniqueConnection);
    m_timer.start();
}

void PromptMessageView::AddHandle(const QString &text)
{
}

void PromptMessageView::AddMessageName(const QString &text)
{
    m_pNameLabel->setText(text);

}

void PromptMessageView::AddMessageTime(const QString &text)
{
    m_pTimeLabel->setText(text);
}

void PromptMessageView::AddMessageContent(const QString &text)
{
    INFO() <<" AddMessageContent = " << text;
    int width = m_pContentLabel->width();
    QFont f;
    f.setPixelSize(24);
    QString str = geteElidedText(f,text,width);
    INFO() <<" AddMessageContent = " << str;
    m_pContentLabel->setText(str);
}

void PromptMessageView::UpdatePosion(const QPoint &point)
{
  this->move(point);
}

void PromptMessageView::Show()
{

    this->show();
}

void PromptMessageView::Finish()
{
    INFO()<<"PromptMessageView::Finish() ++++ ";
    if(IsExistPromptShow())
    {
        if("True" == GetPromptShow())
        {

        }else
        {
            this->hide();
            return;
        }
    }else{
        return;
    }
    if(IsExistPromptMessageName()){
        this->AddMessageName(GetPromptMessageName());
    }
    if(IsExistPromptMessageTime()){
        this->AddMessageTime(GetPromptMessageTime());
    }
    if(IsExistPromptMessageContent()){
        this->AddMessageContent(GetPromptMessageContent());
    }
    if(IsExistPromptButtonA()){
        this->AddBtnA(GetPromptButtonA());
    }
    if(IsExistPromptButtonB())
    {
        this->AddBtnB(GetPromptButtonB());
    }
    if(IsExistPromptHandle()){

    }
    this->Show();

    if(IsExistPromptTime()){
        AddTimer(GetPromptTime());
    }

}

void PromptMessageView::OnTimer()
{
    this->hide();
    emit SigTimerOut(GetPromptId());
}

void PromptMessageView::OnButtonA()
{
    this->hide();
    emit SigButtonClick(GetPromptId(),GetPromptReplyButtonA());
}

void PromptMessageView::OnButtonB()
{
    this->hide();
    emit SigButtonClick(GetPromptId(),GetPromptReplyButtonB());
}

void PromptMessageView::DrawContextA(QString context, QString light)
{

}

void PromptMessageView::DrawContextB(QString context, QString light)
{

}

void PromptMessageView::HighLightText(QString light)
{

}

QString PromptMessageView::geteElidedText(QFont font, const QString& text, int MaxWidth)
{
    QFontMetrics fontWidth(font);

    int width = fontWidth.width(text);  //计算字符串宽度

    QString str = text;
    if(width>=MaxWidth)  //当字符串宽度大于最大宽度时进行转换

    {

        str = fontWidth.elidedText(text,Qt::ElideRight,MaxWidth);  //右部显示省略号

    }

    return str;   //返回处理后的字符串
}
