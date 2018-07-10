#include "PopupGeneralView.h"
#include "HMIFrameWork/log_interface.h"
PopupGeneralView::PopupGeneralView(QWidget *parent)
    :PopUpBase(parent)
    ,m_pBackgroundLabel(NULL)
    ,m_pBackgroundLabelDark(NULL)
    ,m_pLineTop(NULL)
    ,m_pLineBottom(NULL)
    ,m_pVDisplayAreaLayout(NULL)
    ,m_pVDisplayArea(NULL)
    ,m_buttonStyle(ButtonStyle_None)
    ,m_popupStyle(PopupStyle_Default)
{
    this->setGeometry(0,0,800,480);
    m_pBackgroundLabel = new QLabel(this);
    m_pBackgroundLabel->setGeometry(QRect(0,0,800,480));
    m_pBackgroundLabel->setStyleSheet("QLabel{background-color:#99000000}");
    m_pBackgroundLabel->show();

    m_pBackgroundLabelDark = new QLabel(this);
    m_pBackgroundLabelDark->setGeometry(QRect(0,79,800,480-79-85));
    m_pBackgroundLabelDark->setStyleSheet("QLabel{background-color:#000000}");
    m_pBackgroundLabelDark->show();

    m_pVDisplayArea = new QWidget(this);
    m_pVDisplayArea->setGeometry(0,79,800,281);

    m_pLineTop = new QLabel(this);
    m_pLineTop->setPixmap(QPixmap(QString(":/PopUp/Source/images/line_a.png")));
    m_pLineTop->show();


    m_pLineBottom = new QLabel(this);
    m_pLineBottom->setPixmap(QPixmap(QString(":/PopUp/Source/images/line_a.png")));
    m_pLineBottom->show();

    m_TitleLabel = new QLabel(this);
    m_TitleLabel->setGeometry(QRect(0,113,800,40));
    m_TitleLabel->setStyleSheet("color:#FFFFFF;font-size:36px;border:none;background:transparent;");
    m_TitleLabel->setText("Pairing");
    m_TitleLabel->setAlignment(Qt::AlignHCenter);
    m_TitleLabel->hide();

    m_pPasswordLabel = new QLabel(this);
    m_pPasswordLabel->setGeometry(QRect(0,264,800,64));
    m_pPasswordLabel->setStyleSheet("color:#FF4200;font-size:48px;border:none;background:transparent;");
    m_pPasswordLabel->setAlignment(Qt::AlignHCenter);
    m_pPasswordLabel->hide();


    m_pText = new QTextEdit(this);
    m_pText->setStyleSheet("QTextEdit{border:none;background:transparent;}");

    m_pText->setMaximumWidth(800-142-142);
    m_pText->setMinimumWidth(800-142-142);
    m_pText->setMinimumHeight(480-120-32-32-79-38-3);
    m_pText->setMaximumHeight(480-120-32-32-79-38-3);

    m_pText->moveCursor (QTextCursor::Start) ;
    m_pText->ensureCursorVisible() ;
    m_pText->setReadOnly(true);
    m_pText->setFocusPolicy(Qt::NoFocus);
    m_pText->setTextInteractionFlags(Qt::NoTextInteraction);
    m_pBtnA = new QPushButton(this);
    m_pBtnA->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/PopUp/Source/images/button_a.png);}\
                                 QPushButton:pressed{color:#66ffffff;background-image:url(:/PopUp/Source/images/button_a_push.png);border:none;}");
    m_pBtnA->setGeometry(0,0,131,32);
    m_pBtnA->setFocusPolicy(Qt::NoFocus);
    m_pBtnA->setText(QString(tr("Confrim")));
    m_pBtnA->setMaximumWidth(131);
    m_pBtnA->setMinimumWidth(131);
    m_pBtnA->setMinimumHeight(32);
    m_pBtnA->setMaximumHeight(32);
    m_pBtnA->hide();

    m_pBtnB = new QPushButton(this);
    m_pBtnB->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/PopUp/Source/images/button_b.png);}\
                                QPushButton:pressed{color:#66ffffff;background-image:url(:/PopUp/Source/images/button_b_push.png);border:none;}");
    m_pBtnB->setGeometry(0,0,189,32);
    m_pBtnB->setFocusPolicy(Qt::NoFocus);
    m_pBtnB->setText(QString(tr("Cancel")));
    m_pBtnB->setMaximumWidth(189);
    m_pBtnB->setMinimumWidth(189);
    m_pBtnB->setMinimumHeight(32);
    m_pBtnB->setMaximumHeight(32);
    m_pBtnB->hide();


    connect(m_pBtnA,SIGNAL(clicked()),this,SLOT(OnButtonA()),Qt::UniqueConnection);
    connect(m_pBtnB,SIGNAL(clicked()),this,SLOT(OnButtonB()),Qt::UniqueConnection);
    m_pHDisplayAreaLayout = new QHBoxLayout();
    m_pHDisplayArea = new QWidget();
    m_pHDisplayArea->setGeometry(0,0,800,32);

    m_pVDisplayAreaLayout = new QVBoxLayout();
}

void PopupGeneralView::AddTitle(const QString &title)
{
    m_popupStyle = PopupStyle_Title;
    m_TitleLabel->setText(title);
    m_TitleLabel->show();
}

void PopupGeneralView::AddContextA(const QString &text)
{
    Q_UNUSED(text)
}

void PopupGeneralView::AddContextALight(const QString &text)
{
    Q_UNUSED(text)
}

void PopupGeneralView::AddContextB(const QString &text)
{
    Q_UNUSED(text)
}

void PopupGeneralView::AddContextBLight(const QString &text)
{
    Q_UNUSED(text)
}

void PopupGeneralView::AddPassword(const QString &text)
{
    m_pPasswordLabel->setText(text);
    m_pPasswordLabel->show();
}

void PopupGeneralView::AddBtnA(const QString &text)
{
    m_pBtnA->setText(text);

    QFont wordfont;
    //wordfont.setFamily("宋体");
    wordfont.setPointSize(24);
    QFontMetrics fm(wordfont);
    QLabel m_text;
    m_text.setText(text);
    QRect rec = fm.boundingRect( m_text.text());
    int ii = rec.width();//这个就获得了字符串所占的像素宽度

    if(ii > 126)
    {
        m_buttonStyle = ButtonStyle_BtnAS;
        m_pBtnA->resize(189,32);
        m_pBtnA->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/PopUp/Source/images/button_b.png);}\
                                    QPushButton:pressed{color:#66ffffff;background-image:url(:/PopUp/Source/images/button_b_push.png);border:none;}");
        m_pBtnA->setMaximumWidth(189);
        m_pBtnA->setMinimumWidth(189);
        m_pBtnA->setMinimumHeight(32);
        m_pBtnA->setMaximumHeight(32);
    }else
    {
        m_buttonStyle = ButtonStyle_BtnA;
        m_pBtnA->resize(131,32);
        m_pBtnA->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/PopUp/Source/images/button_a.png);}\
                                     QPushButton:pressed{color:#66ffffff;background-image:url(:/PopUp/Source/images/button_a_push.png);border:none;}");
        m_pBtnA->setMaximumWidth(131);
        m_pBtnA->setMinimumWidth(131);
        m_pBtnA->setMinimumHeight(32);
        m_pBtnA->setMaximumHeight(32);
    }
    m_pBtnA->show();
}

void PopupGeneralView::AddBtnB(const QString &text)
{

    m_pBtnB->setText(text);
    QFont wordfont;
    //wordfont.setFamily("宋体");
    wordfont.setPointSize(24);
    QFontMetrics fm(wordfont);
    QLabel m_text;
    m_text.setText(text);
    QRect rec = fm.boundingRect( m_text.text());
    int ii = rec.width();//这个就获得了字符串所占的像素宽度
    if(ii > 126)
    {
        if(ButtonStyle_BtnAS == m_buttonStyle)
        {
            m_buttonStyle = ButtonStyle_BtnABS;
        }else
        {
            m_buttonStyle = ButtonStyle_BtnBS;
        }
        m_pBtnB->resize(189,32);
        m_pBtnB->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/PopUp/Source/images/button_b.png);}\
                                    QPushButton:pressed{color:#66ffffff;background-image:url(:/PopUp/Source/images/button_b_push.png);border:none;}");
        m_pBtnB->setMaximumWidth(189);
        m_pBtnB->setMinimumWidth(189);
        m_pBtnB->setMinimumHeight(32);
        m_pBtnB->setMaximumHeight(32);
    }else
    {
        if(ButtonStyle_BtnAS != m_buttonStyle)
        {
            m_buttonStyle = ButtonStyle_BtnB;
        }
        m_pBtnB->resize(131,32);
        m_pBtnB->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/PopUp/Source/images/button_a.png);}\
                                     QPushButton:pressed{color:#66ffffff;background-image:url(:/PopUp/Source/images/button_a_push.png);border:none;}");
        m_pBtnB->setMaximumWidth(131);
        m_pBtnB->setMinimumWidth(131);
        m_pBtnB->setMinimumHeight(32);
        m_pBtnB->setMaximumHeight(32);
    }
    m_pBtnB->show();
}

void PopupGeneralView::AddTimer(int time)
{
    m_timer.setInterval(time);
    m_timer.setSingleShot(true);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(OnTimer()),Qt::UniqueConnection);
    m_timer.start();
}

void PopupGeneralView::AddHandle(const QString &text)
{
    Q_UNUSED(text)
}

void PopupGeneralView::Show()
{
    switch (m_popupStyle) {
    case PopupStyle_Default:
    {
        m_pHDisplayAreaLayout->setSpacing(80);
        if(ButtonStyle_BtnBS  == m_buttonStyle)
        {
            m_pHDisplayAreaLayout->addSpacing(58);
        }
        m_pHDisplayAreaLayout->addWidget(m_pBtnA,0,Qt::AlignRight|Qt::AlignVCenter);
        m_pHDisplayAreaLayout->addWidget(m_pBtnB,0,Qt::AlignLeft|Qt::AlignVCenter);
        if(ButtonStyle_BtnAS  == m_buttonStyle)
        {
            m_pHDisplayAreaLayout->addSpacing(58);
        }
        m_pHDisplayArea->setLayout(m_pHDisplayAreaLayout);

        m_pVDisplayAreaLayout->setSpacing(30);
        m_pVDisplayAreaLayout->addWidget(m_pLineTop,3,Qt::AlignTop|Qt::AlignHCenter);
        //m_pVDisplayAreaLayout->addWidget(m_TitleLabel,40,Qt::AlignTop|Qt::AlignHCenter);
        m_pVDisplayAreaLayout->addStretch(8);
        m_pVDisplayAreaLayout->addWidget(m_pText,480-120-32-32-79-38-3,Qt::AlignTop|Qt::AlignHCenter);
        if(IsExistPassword())
        {
            m_pVDisplayAreaLayout->addSpacing(30);
            m_pVDisplayAreaLayout->addWidget(m_pPasswordLabel,64,Qt::AlignCenter);
        }
        if(ButtonStyle_None != m_buttonStyle)
        {
            m_pVDisplayAreaLayout->addWidget(m_pHDisplayArea,32,Qt::AlignBottom|Qt::AlignHCenter);
            m_pHDisplayArea->show();
        }else
        {
            m_pHDisplayArea->hide();
        }
        m_pVDisplayAreaLayout->addWidget(m_pLineBottom,3,Qt::AlignBottom|Qt::AlignHCenter);
        m_pVDisplayArea->setGeometry(0,79,800,480-79-85);
        m_pVDisplayArea->setLayout(m_pVDisplayAreaLayout);
    }
        break;
    case PopupStyle_Title:
    {

        m_pHDisplayAreaLayout->setSpacing(80);
        if(ButtonStyle_BtnBS  == m_buttonStyle)
        {
            m_pHDisplayAreaLayout->addSpacing(58);
        }
        m_pHDisplayAreaLayout->addWidget(m_pBtnA,0,Qt::AlignRight|Qt::AlignVCenter);
        m_pHDisplayAreaLayout->addWidget(m_pBtnB,0,Qt::AlignLeft|Qt::AlignVCenter);
        if(ButtonStyle_BtnAS  == m_buttonStyle)
        {
            m_pHDisplayAreaLayout->addSpacing(58);
        }
        m_pHDisplayArea->setLayout(m_pHDisplayAreaLayout);

        m_pVDisplayAreaLayout->setSpacing(30);
        m_pVDisplayAreaLayout->addWidget(m_pLineTop,3,Qt::AlignTop|Qt::AlignHCenter);
        m_pVDisplayAreaLayout->addWidget(m_TitleLabel,40,Qt::AlignTop|Qt::AlignHCenter);
        m_pVDisplayAreaLayout->addStretch(15);
        m_pVDisplayAreaLayout->addWidget(m_pText,480-120-32-32-79-38-3,Qt::AlignTop|Qt::AlignHCenter);        
        if(ButtonStyle_None != m_buttonStyle)
        {
            m_pVDisplayAreaLayout->addWidget(m_pHDisplayArea,32,Qt::AlignBottom|Qt::AlignHCenter);
            m_pHDisplayArea->show();
        }else
        {
            m_pHDisplayArea->hide();
        }
        m_pVDisplayAreaLayout->addWidget(m_pLineBottom,3,Qt::AlignBottom|Qt::AlignHCenter);

        m_pVDisplayArea->setGeometry(0,79,800,480-79-85);
        m_pVDisplayArea->setLayout(m_pVDisplayAreaLayout);
    }
        break;
    default:
        break;
    }
    if(IsExistPopUpContextA())
    {
        DrawContextA(GetPopUpContextA(),GetPopUpContextALight());
    }
    if(IsExistPopUpContextB())
    {
        DrawContextB(GetPopUpContextB(),GetPopUpContextBLight());
    }
    this->show();
}

void PopupGeneralView::Finish()
{
    if(IsExistPopUpShow())
    {
        if("True" == GetPopUpShow())
        {

        }else
        {
            this->hide();
            return;
        }
    }else{
        return;
    }

    if(IsExistPopUpTitle()){
        this->AddTitle(GetPopUpTitle());
    }
    if(IsExistPopUpContextA()){
        this->AddContextA(GetPopUpContextA());
    }
    if(IsExistPopUpContextB()){
        this->AddContextB(GetPopUpContextB());
    }
    if(IsExistPopUpContextALight()){
        this->AddContextALight(GetPopUpContextALight());
    }
    if(IsExistPopUpContextBLight()){
        this->AddContextBLight(GetPopUpContextBLight());
    }
    if(IsExistPassword()){
        this->AddPassword(GetPassword());
    }
    if(IsExistPopUpButtonA()){
        this->AddBtnA(GetPopUpButtonA());
    }
    if(IsExistPopUpButtonB())
    {
        this->AddBtnB(GetPopUpButtonB());
    }
    if(IsExistPopUpHandle()){

    }
    this->Show();

    if(IsExistPopUpTime()){
        AddTimer(GetPopUpTime());
    }

}

void PopupGeneralView::OnTimer()
{
    this->hide();
    emit SigTimerOut(GetPopUpId());
}

void PopupGeneralView::OnButtonA()
{
    this->hide();
    emit SigButtonClick(GetPopUpId(),GetPopUpReplyButtonA());
}

void PopupGeneralView::OnButtonB()
{
    this->hide();
    emit SigButtonClick(GetPopUpId(),GetPopUpReplyButtonB());
}


void PopupGeneralView::DrawContextA(QString context, QString light)
{

    //font size
    QFont font;
    font.setPixelSize(24);
    m_pText->setCurrentFont(font);
    m_pText->setTextColor(QColor(QString("#ffffff")));

    //height of line
    QTextCursor textCursor = m_pText->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(38, QTextBlockFormat::FixedHeight);//设置固定行高
    textCursor.setBlockFormat(textBlockFormat);
    m_pText->setTextCursor(textCursor);

    m_pText->insertPlainText(context);

    //highlight
    this->HighLightText(light);
}

void PopupGeneralView::DrawContextB(QString context, QString light)
{

    //font size
    QFont font;
    font.setPixelSize(20);
    m_pText->setCurrentFont(font);
    m_pText->setTextColor(QColor(QString("#ffffff")));

    //height of line
    QTextCursor textCursor = m_pText->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(34, QTextBlockFormat::FixedHeight);//设置固定行高
    textCursor.setBlockFormat(textBlockFormat);
    m_pText->setTextCursor(textCursor);

    m_pText->insertPlainText(context);

    //highlight
    this->HighLightText(light);
}

void PopupGeneralView::HighLightText(QString light)
{
    QString search_text = light;
        if (search_text.trimmed().isEmpty()) {
//            QMessageBox::information(this, tr("Empty search field"), tr("The search field is empty."));
        } else {
            QTextDocument *document = m_pText->document();
            bool found = false;
            QTextCursor highlight_cursor(document);
            QTextCursor cursor(document);
            //开始
            cursor.beginEditBlock();
            QTextCharFormat color_format(highlight_cursor.charFormat());
            color_format.setForeground(QColor("#ffb121"));
            while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
                //查找指定的文本，匹配整个单词
                highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
                if (!highlight_cursor.isNull()) {
                    if(!found)
                        found = true;
                    highlight_cursor.mergeCharFormat(color_format);
                }
            }
            cursor.endEditBlock();
            //结束
            if (false == found) {
                INFO("the word cannot be found.");
//                QMessageBox::information(this, tr("Word not found"), tr("Sorry,the word cannot be found."));
            }
        }
}
