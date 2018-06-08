#include "PromptNavView.h"
#include "HMIFrameWork/log_interface.h"
PromptNavView::PromptNavView(QWidget *parent)
    :PromptBase(parent)
    ,m_pNavDirectionIconLabel(NULL)
    ,m_pNavDistanceLabel(NULL)
    ,m_pNavSceneDescriptionLabel(NULL)
    ,m_pNavDestinationLabel(NULL)
    ,m_pBtnA(NULL)
{
    this->setGeometry(0,0,800,102);
    this->setStyleSheet("QWidget{background:transparet;}");
    m_pBtnA = new QPushButton(this);
    m_pBtnA->setGeometry(QRect(0,0,800,102));
    m_pBtnA->setStyleSheet("QPushButton{border:nonr;background:transparent;}");
    m_pBtnA->setFocusPolicy(Qt::NoFocus);
    m_pBtnA->show();

    m_pNavDirectionIconLabel = new QLabel(this);
    m_pNavDirectionIconLabel->setGeometry(QRect(183,26,33,45));
    m_pNavDirectionIconLabel->setStyleSheet("QLabel{border-image:url(:/Prompt/Source/images/left_arrow.png);background:transparent;color:rgb(48,48,48);font-size:26px;}");
    m_pNavDirectionIconLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
    m_pNavDirectionIconLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pNavDirectionIconLabel->setMinimumSize(QSize(33,45));
    m_pNavDirectionIconLabel->show();

    m_pNavDistanceLabel = new QLabel(this);
    m_pNavDistanceLabel->setGeometry(QRect(229,33,112,48));
    m_pNavDistanceLabel->setStyleSheet("QLabel{border:none;background:transparent;color:rgb(255,177,33);font-size:36px;}");
    m_pNavDistanceLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
    m_pNavDistanceLabel->setMargin(0);
    m_pNavDistanceLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pNavDistanceLabel->show();

    m_pNavSceneDescriptionLabel = new QLabel(this);
    m_pNavSceneDescriptionLabel->setGeometry(QRect(354,41,84,33));
    m_pNavSceneDescriptionLabel->setStyleSheet("QLabel{border:none;background:transparent;color:rgb(255,255,255);font-size:24px;}");
    m_pNavSceneDescriptionLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
    m_pNavSceneDescriptionLabel->setMargin(0);
    m_pNavSceneDescriptionLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pNavSceneDescriptionLabel->show();

    m_pNavDestinationLabel = new QLabel(this);
    m_pNavDestinationLabel->setGeometry(QRect(451,38,247,41));
    m_pNavDestinationLabel->setStyleSheet("QLabel{border:none;background:transparent;color:rgb(255,255,255);font-size:30px;}");
    m_pNavDestinationLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
    m_pNavDestinationLabel->setMargin(0);
    m_pNavDestinationLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pNavDestinationLabel->show();

    connect(m_pBtnA,SIGNAL(clicked()),this,SLOT(OnButtonA()),Qt::UniqueConnection);
}

PromptNavView::~PromptNavView()
{

}

void PromptNavView::AddTitle(const QString &title)
{

}

void PromptNavView::AddContextA(const QString &text)
{

}

void PromptNavView::AddContextALight(const QString &text)
{

}

void PromptNavView::AddContextB(const QString &text)
{

}

void PromptNavView::AddContextBLight(const QString &text)
{

}

void PromptNavView::AddBtnA(const QString &text)
{
    m_pBtnA->setText(text);
    m_pBtnA->lower();
    m_pBtnA->show();
}

void PromptNavView::AddBtnB(const QString &text)
{

}

void PromptNavView::AddTimer(int time)
{
    m_timer.setInterval(time);
    m_timer.setSingleShot(true);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(OnTimer()),Qt::UniqueConnection);
    m_timer.start();
}

void PromptNavView::AddHandle(const QString &text)
{
}

void PromptNavView::AddNavDirection(const QString &text)
{
    if("TurnLeft" == text)
    {

    }else if("TurnReft" == text)
    {

    }
}

void PromptNavView::AddNavDistance(const QString &text)
{
    QFont font ;
    font.setPixelSize(36);
    m_pNavDistanceLabel->setFont(font);
    int width = getTextWidth(font,text);
    QFont font2 ( "Microsoft YaHei", 36, 63);
    m_pNavDistanceLabel->setFont(font2);
    m_pNavDistanceLabel->resize(width,m_pNavDistanceLabel->height());
    m_pNavDistanceLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
    INFO()<<"m_pNavDistanceLabel = " << width;
    m_pNavDistanceLabel->setText(text);
}

void PromptNavView::AddNavSceneDescription(const QString &text)
{
    QFont font;
    font.setPixelSize(24);
    m_pNavSceneDescriptionLabel->setFont(font);
    int width = getTextWidth(font,text);
    m_pNavSceneDescriptionLabel->resize(width,m_pNavSceneDescriptionLabel->height());
    m_pNavSceneDescriptionLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
     INFO()<<"m_pNavSceneDescriptionLabel = " << width;
    m_pNavSceneDescriptionLabel->setText(text);
}

void PromptNavView::AddNavDestination(const QString &text)
{
    QFont font ( "Microsoft YaHei", 30, 63);
    m_pNavDestinationLabel->setFont(font);
    int width = getTextWidth(font,text);
    m_pNavDestinationLabel->resize(width,m_pNavDestinationLabel->height());
    m_pNavDestinationLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
     INFO()<<"m_pNavDistanceLabel = " << width;
    m_pNavDestinationLabel->setText(text);
}


void PromptNavView::UpdatePosition()
{
    int viewWidth = m_pNavDirectionIconLabel->width()+ m_pNavDistanceLabel->width()+m_pNavSceneDescriptionLabel->width()+m_pNavDestinationLabel->width();
    if(viewWidth > 692)
    {
        int width = 692 -(m_pNavDirectionIconLabel->width()+ m_pNavDistanceLabel->width()+m_pNavSceneDescriptionLabel->width());
        m_pNavDestinationLabel->resize(width,m_pNavDestinationLabel->height());

        QFont f( "Microsoft YaHei", 30, 63);
        QString str = geteElidedText(f,m_pNavDestinationLabel->text(),width);
        INFO() <<" AddMessageContent = " << str;
        m_pNavDestinationLabel->setText(str);

    }

     viewWidth = m_pNavDirectionIconLabel->width()+ m_pNavDistanceLabel->width()+m_pNavSceneDescriptionLabel->width()+m_pNavDestinationLabel->width();

    m_pNavDirectionIconLabel->move((800-viewWidth)/2+13,m_pNavDirectionIconLabel->y());
    m_pNavDistanceLabel->move(m_pNavDirectionIconLabel->x()+m_pNavDirectionIconLabel->width()+13,m_pNavDistanceLabel->y());
    m_pNavSceneDescriptionLabel->move(m_pNavDistanceLabel->x()+m_pNavDistanceLabel->width()+13,m_pNavSceneDescriptionLabel->y());
    m_pNavDestinationLabel->move(m_pNavSceneDescriptionLabel->x()+m_pNavSceneDescriptionLabel->width()+13,m_pNavDestinationLabel->y());

    INFO() <<" " <<m_pNavDirectionIconLabel->geometry() <<" "<<m_pNavDistanceLabel->geometry() <<" "<<m_pNavSceneDescriptionLabel->geometry()<<" "<<m_pNavDestinationLabel->geometry();


}

void PromptNavView::Show()
{

    this->show();
}

void PromptNavView::Finish()
{
    INFO()<<"PromptNavView::Finish() ++++ ";
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
    if(IsExistPromptNavDirection()){
        this->AddNavDirection(GetPromptNavDirection());
    }
    if(IsExistPromptNavDistance()){
        this->AddNavDistance(GetPromptNavDistance());
    }
    if(IsExistPromptNavSceneDescription()){
        this->AddNavSceneDescription(GetPromptNavSceneDescription());
    }
    if(IsExistPromptNavDestination()){
        this->AddNavDestination(GetPromptNavDestination());
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

    UpdatePosition();
    this->Show();

    if(IsExistPromptTime()){
        AddTimer(GetPromptTime());
    }

}

void PromptNavView::OnTimer()
{
    this->hide();
    emit SigTimerOut(GetPromptId());
}

void PromptNavView::OnButtonA()
{
    this->hide();
    emit SigButtonClick(GetPromptId(),GetPromptReplyButtonA());
}

void PromptNavView::DrawContextA(QString context, QString light)
{

}

void PromptNavView::DrawContextB(QString context, QString light)
{

}

void PromptNavView::HighLightText(QString light)
{

}

QString PromptNavView::geteElidedText(QFont font, const QString& text, int MaxWidth)
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

int PromptNavView::getTextWidth(QFont font, const QString &text)
{
    QFontMetrics fontWidth(font);

    return fontWidth.width(text);  //计算字符串
}
