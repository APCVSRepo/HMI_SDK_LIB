#include "CListWidgetItem.h"
#include <QRegularExpression>
#include <QDate>

CListWidgetItem::CListWidgetItem()
    : m_nSpecifiedID(-1)
    , m_nSpecifiedIDStatus(-1)
    , m_lluSpecifiedTrackID(0)
    , m_qsPhoneNum("")
    , m_bMatchPhoneNumber(false)
    , m_nLineSpacing(0)
{
    ;
}

CListWidgetItem::CListWidgetItem(const QSize &sizeBg)
    : m_sizeItem(sizeBg)
    , m_nSpecifiedID(0)
    , m_nSpecifiedIDStatus(-1)
    , m_lluSpecifiedTrackID(0)
    , m_qsPhoneNum("")
    , m_bMatchPhoneNumber(false)
    , m_nLineSpacing(0)
{
}

CListWidgetItem::~CListWidgetItem()
{

}

void CListWidgetItem::SetBackgroundInfo(const QString &qsNormalPath,
                                        const QString &qsPressedPath,
                                        const QString &qsCursoredPath)
{
    m_qsListBackground << qsNormalPath << qsPressedPath << qsCursoredPath;
}

void CListWidgetItem::AddText(const QRect &rect, const QString &text, int flags, int fontSize,QColor color)
{
    m_textRectList << rect;
    m_textStringList << text;
    m_textAlignList << flags;
    m_textColorList << color;
    m_textSizeList << fontSize;
    m_textTypeList << false;
}

void CListWidgetItem::AddSpecialText(const QRect &rect, const QString &text, int flags, int fontSize)
{
    m_textRectList << rect;
    m_textStringList << text;
    m_textAlignList << flags;
    m_textColorList << QColor(255, 255, 255);
    m_textSizeList << fontSize;
    m_textTypeList << true;
    //
    QFont font;
    font.setPixelSize(fontSize);
    QFontMetrics fontMetrics(font);
    int fontHeight = fontMetrics.height();
    if (CheckHighlightText(text))
    {
        int left = 0;
        int top  = rect.top();
        for (int i = 0; i < m_qsListText.count(); i++)
        {
            QString qsText = m_qsListText.at(i);
            int textType = m_listSpecialTextType.at(i);
            int remainderWidth = rect.width() - left;
            if(0>remainderWidth)
            {
                remainderWidth = 0;
            }
          //  Log("remainderWidth = %d, qsText = %s, textType = %d", remainderWidth, qsText.toStdString().c_str(), textType);
            if (m_listSpecialTextType.at(i))
            {
                CountHighlightText(qsText, rect, textType, fontSize, remainderWidth, left, top);
            }
            else
            {
                CountNormalText(qsText, rect, textType, fontSize, remainderWidth, left, top);
            }
        }
        m_sizeItem.setHeight(top + fontHeight + 5);
    }
    else
    {
//        QRect fontRect = fontMetrics.boundingRect(rect, Qt::TextWrapAnywhere, text);
//        Log("2222222222remainderWidth = %d, qsText = %s, textType = %d", fontRect.width(), text.toStdString().c_str(), 0);
//        m_specialTextRectList << fontRect;
//        m_specialTextStringList << text;
//        m_specialTextTypeList << 0;
//        m_sizeItem.setHeight(rect.top() + fontRect.height() + 5);
       QFont font;
       font.setPixelSize(fontSize);
       QFontMetrics fontMetrics(font);
        int fontHeight = fontMetrics.height();
       int left = 0;
       int top  = rect.top();
       QString qsText = text;
       int remainderWidth = rect.width() - left;
       if(0>remainderWidth)
       {
           remainderWidth = 0;
       }
  //     Log("remainderWidth = %d, qsText = %s,", remainderWidth, qsText.toStdString().c_str());
         CountNormalText(qsText, rect, 0, fontSize, remainderWidth, left, top);
         m_sizeItem.setHeight(top + fontHeight+ 5);
    }
}

void CListWidgetItem::AddIcon(const QRect &rect, const QPixmap &pixmap, bool bIndicator, bool bShow)
{
    m_iconRectList << rect;
    m_iconPixmapList << pixmap;
    m_iconIndicatorList << bIndicator;
    m_iconShowHideList << bShow;
}

void CListWidgetItem::AddButton(const QRect &rect, const QStringList pathList,
                                CListWidgetItem::eButtonState state, bool bIndicator, int mode)
{
    m_buttonRectList << rect;
    m_buttonPathList << pathList;
    int nState = state;
    m_buttonStateList << nState;
    m_buttonIndicatorList << bIndicator;
    m_buttonBgDrawModeList << mode;
}

void CListWidgetItem::AddCheckBox(const QRect &rect, const QPixmap &pixmapBg, const QPixmap &pixmapCheck, bool bChecked)
{
    m_checkBoxRectList << rect;
    m_checkBoxBgPixmapList << pixmapBg;
    m_checkBoxCheckPixmapList << pixmapCheck;
    m_checkBoxStateList << bChecked;
}

void CListWidgetItem::SetSpecifiedID(int id)
{
    m_nSpecifiedID = id;
}

void CListWidgetItem::SetSpecifiedIDStatus(int Status)
{
    m_nSpecifiedIDStatus = Status;
}

void CListWidgetItem::SetSpecifiedTrackID(unsigned long long id)
{
    m_lluSpecifiedTrackID = id;
}

void CListWidgetItem::SetSpecifiedNum(QString text)
{
    m_qsPhoneNum = text;
}

void CListWidgetItem::SetTitleName(const QString &name)
{
    m_qsTitleName = name;
}

bool CListWidgetItem::IsPhoneNumber(const QString &qsNumber)
{
    QRegExp rx;
    rx.setPatternSyntax(QRegExp::RegExp);
    rx.setPattern("(^((\\+86)|(86))?(13|15|18)\\d{9}$\\+$)");
    return rx.exactMatch(qsNumber);
}

bool CListWidgetItem::IsDate(QString &qsDate)
{
    if (qsDate.contains("年"))
    {
        qsDate.replace("年", "/");
    }
    if (qsDate.contains("月"))
    {
        qsDate.replace("月", "/");
    }
    if (qsDate.contains("日"))
    {
        qsDate.remove("日");
    }
    else if(qsDate.contains("号"))
    {
        qsDate.remove("号");
    }

    QStringList qsList;
    if (qsDate.contains("/"))
    {
        qsList = qsDate.split("/");
    }
    else if (qsDate.contains("-"))
    {
        qsList = qsDate.split("-");
    }
    if (2 == qsList.count())
    {
        int nDate1 = qsList.at(0).toInt();
        int nDate2 = qsList.at(1).toInt();
        if (nDate1 > 0 && nDate1 < 13 && nDate2 > 0 && nDate2 < 32)
        {
            return true;
        }
    }
    else if (3 == qsList.count())
    {
        int nDate1 = qsList.at(0).toInt();
        int nDate2 = qsList.at(1).toInt();
        int nDate3 = qsList.at(2).toInt();
        QDate date(nDate1, nDate2, nDate3);
        if (date.isValid() && date.year() >= 2013 && date.year() <= 2063) //2013~ 2063
        {
            return true;
        }
        QDate date1(nDate3, nDate1, nDate2);
        if (date1.isValid())
        {
            return true;
        }
    }
    else
    {
        return false;
    }
    return false;
}

bool CListWidgetItem::IsTime(QString &qsTime)
{
    QStringList qsList;
    if (qsTime.contains(":"))
    {
        qsList = qsTime.split(":");
    }
    else if (qsTime.contains("："))
    {
        qsList = qsTime.split("：");
    }
    if (2 == qsList.count())
    {
        int nTime1 = qsList.at(0).toInt();
        int nTime2 = qsList.at(1).toInt();
        if (nTime1 >= 0 && nTime1 < 24 && nTime2 >= 0 && nTime2 < 60)
        {
            return true;
        }
    }
    else if (3 == qsList.count())
    {
        int nTime1 = qsList.at(0).toInt();
        int nTime2 = qsList.at(1).toInt();
        int nTime3 = qsList.at(2).toInt();
        if (nTime1 >= 0 && nTime1 < 24 && nTime2 >= 0 && nTime2 < 60 && nTime3 >= 0 && nTime3 < 60)
        {
            return true;
        }
    }
    else
    {
        return false;
    }
    return false;
}

bool CListWidgetItem::CheckHighlightText(const QString &qsText)
{
    bool bHasHighlightText = false;
    int posHighlightText = 0;
    int posOther = 0;

    QString qsNumber = "(([¥|￥|$|＄|₤|£|￡|€|¢|￠]\\d{1,})|(\\d{1,}[百|千|万|亿|元|年|分|秒|克])|(\\d{1,}[.]\\d{1,})|(\\d{3,15}))";

    QString qsDateReg1 = "(\\d{1,}(/|-)\\d{1,}(/|-)\\d{1,})";
    QString qsDateReg2 = "(\\d{1,}(/|-)\\d{1,})";
    QString qsDateReg3 = "(\\d{1,}(年)\\d{1,}(月)\\d{1,}(日|号))";
    QString qsDateReg4 = "(\\d{1,}(月)\\d{1,}(日|号))";
    QString qsDateReg = "(" + qsDateReg1 + "|" + qsDateReg2 + "|" + qsDateReg3 + "|" + qsDateReg4 + ")";

    QString qsTimeReg1 = "(\\d{1,}(:|：)\\d{1,}(:|：)\\d{1,})";
    QString qsTimeReg2 = "(\\d{1,}(:|：)\\d{1,})";
    QString qsTimeReg = "(" + qsTimeReg1 + "|" + qsTimeReg2 + ")";

    QString qsSpecialDateReg1 = "((今天)|(明天)|(后天)|(大后天)|((下周|下下周|星期|周|礼拜)(一|二|三|四|五|六|日|天)))"
                               "(()|(早上)|(上午)|(中午)|(下午)|(晚上))"
                               "(()|([0-9]|[0-1][0-9]|[2][0-3])(点))";

    QString qsSpecialDateReg2 = "((早上)|(上午)|(中午)|(下午)|(晚上))";

    QString qsSpecialDateReg3 = "((早上)|(上午)|(中午)|(下午)|(晚上)|())(([0-9]|[0-1][0-9]|[2][0-3])(点))";

    QString qsSpecialDateReg4 = "(Monday|Mon\\.|Tuesday|Tues\\.|Wednesday|Wed\\.|Thursday|Thur\\."
                                "|Friday|Fri\\.|Saturday|Sat\\.|Sunday|Sun\\.)";

    QString qsSpecialDateReg = "(" + qsSpecialDateReg1 + "|" + qsSpecialDateReg2 + "|"
            + qsSpecialDateReg3 + "|" + qsSpecialDateReg4 + ")";

    QString qsDateTimeReg = "(" + qsDateReg + "|" + qsTimeReg + "|"+ qsSpecialDateReg + ")";
    QString qsHighlightReg = "(" + qsNumber + "|" + qsDateTimeReg + ")";
    QRegExp rx(qsHighlightReg);

    while ((posHighlightText= rx.indexIn(qsText, posHighlightText)) != -1)
    {
        if (posHighlightText != posOther)
        {
            m_qsListText << qsText.mid(posOther, posHighlightText-posOther);
            m_listSpecialTextType << 0;
        }
        QString qsHighlightText = rx.cap();

        QRegularExpression re("(^\\d+$)|((\\d{2,}(-)\\d{3,}))");
        if (qsHighlightText.contains(re)) //phone number
        {
            if (qsHighlightText.length() > 2)
            {
                m_listSpecialTextType << 1;
                bHasHighlightText = true;
            }
            else
            {
                m_listSpecialTextType << 0;
            }
        }
        else if (IsDate(qsHighlightText)) //Date
        {
            m_listSpecialTextType << 2;
            bHasHighlightText = true;
        }
        else if (IsTime(qsHighlightText)) //Time
        {
            m_listSpecialTextType << 2;
            bHasHighlightText = true;
        }
        else if (qsHighlightText.contains("星") ||
                 qsHighlightText.contains("a") ||
                 qsHighlightText.contains("u") ||
                 qsHighlightText.contains("e") ||
                 qsHighlightText.contains("o") ||
                 qsHighlightText.contains("i") ||
                 qsHighlightText.contains("周") ||
                 qsHighlightText.contains("天") ||
                 qsHighlightText.contains("礼拜") ||
                 qsHighlightText.contains("午") ||
                 qsHighlightText.contains("上") ||
                 qsHighlightText.contains("点")||
                 qsHighlightText.contains("日")) //special date
        {
            m_listSpecialTextType << 3;
            bHasHighlightText = true;
        }
        else
        {
            m_listSpecialTextType << 0;
        }
        posHighlightText += rx.matchedLength();
        posOther = posHighlightText;
        m_qsListText << rx.cap();
    }
    if (posOther != qsText.count())
    {
        m_qsListText << qsText.mid(posOther, qsText.count() - posOther);
        m_listSpecialTextType << 0;
    }

    return bHasHighlightText;
}

void CListWidgetItem::CountHighlightText(QString& text, const QRect &rect, int textType, int fontSize, int remainderWidth, int &left, int &top)
{
    QFont font;
    font.setPixelSize(fontSize);
    QFontMetrics fontMetrics(font);
    //
    int textWidth = fontMetrics.width(text);
    int fontHeight = fontMetrics.height();
    if (textWidth > remainderWidth)
    {
        top += fontHeight;
        m_specialTextRectList << QRect(rect.left(), top, textWidth+5, fontHeight);
        m_specialTextStringList << text;
        m_specialTextTypeList << textType;
        left = textWidth+5;
    }
    else
    {
        m_specialTextRectList << QRect(left+rect.left(), top, textWidth+5, fontHeight);
        m_specialTextStringList << text;
        m_specialTextTypeList << textType;
        left += textWidth+5;
    }
}

void CListWidgetItem::CountNormalText(QString& text, const QRect &rect, int textType, int fontSize, int remainderWidth, int &left, int &top)
{
    //Log("[CListWidgetItem::CountNormalText]Start: left = %d, top = %d", left, top);
    QFont font;
    font.setPixelSize(fontSize+1);
    QFontMetrics fontMetrics(font);
    int fontHeight = fontMetrics.height();
    //
    if (text.contains("\n"))
    {
        QStringList qsTextList = text.split("\n");
        int textWidth = 0;
        for (int j = 0; j < qsTextList.count(); j++)
        {
            QString qsText = qsTextList.at(j);
            int tempWidth = 0;
            int index = 0;
            for (int textCount = 0; textCount < qsText.count(); textCount++)
            {
                tempWidth += fontMetrics.width(qsText.at(textCount), 1);
                if (tempWidth > remainderWidth)
                {
                    QString qsWrapText1 = qsText.left(textCount);
                    m_specialTextRectList << QRect(left+rect.left(), top, remainderWidth, fontHeight);
                    m_specialTextStringList << qsWrapText1;
                    m_specialTextTypeList << textType;
                    left = 0;
                    top += fontHeight;
                    index = textCount;
                    //Log("[CListWidgetItem::CountNormalText]: qsWrapText1 = %s", qsWrapText1.toStdString().c_str());
                    //Log("[CListWidgetItem::CountNormalText]End with \\n: left = %d, top = %d", left, top);
                    break;
                }
            }
            QString qsWrapText2 = qsText.right(qsText.count() - index);
            //Log("[CListWidgetItem::CountNormalText]: qsWrapText2 = %s", qsWrapText2.toStdString().c_str());
            CountTextRect(fontMetrics, qsWrapText2, rect, textType, left, top);
            textWidth = left;
            top += fontHeight;
            left = 0;
            remainderWidth = rect.width();
            //Log("[CListWidgetItem::CountNormalText]End with \\n: left = %d, top = %d", left, top);
        }
        top -= fontHeight;
        left = textWidth + 5;
        //Log("[CListWidgetItem::CountNormalText]End with \\n: left = %d, top = %d", left, top);
    }
    else
    {
        QString qsText = text;
        int tempWidth = 0;
        int index = 0;
        for (int textCount = 0; textCount < qsText.count(); textCount++)
        {
            tempWidth += fontMetrics.width(qsText.at(textCount), 1);
            if (tempWidth > remainderWidth)
            {
                QString qsWrapText1 = qsText.left(textCount);
                m_specialTextRectList << QRect(left+rect.left(), top, remainderWidth, fontHeight);
                m_specialTextStringList << qsWrapText1;
                m_specialTextTypeList << textType;
                left = 0;
                top += fontHeight;
                index = textCount;
                //Log("[CListWidgetItem::CountNormalText]: qsWrapText1 = %s", qsWrapText1.toStdString().c_str());
                break;
            }
        }
        QString qsWrapText2 = qsText.right(qsText.count() - index);
        CountTextRect(fontMetrics, qsWrapText2, rect, textType, left, top);
        //Log("[CListWidgetItem::CountNormalText]End: left = %d, top = %d", left, top);
    }
}

void CListWidgetItem::CountTextRect(const QFontMetrics &fontMetrics, QString& text, const QRect &rect, int textType, int &left, int &top)
{
    int textWidth = fontMetrics.width(text);
    int fontHeight = fontMetrics.height();
    if (textWidth <= rect.width())
    {
        QRect textRect(left+rect.left(), top, rect.width(), fontHeight);
        m_specialTextRectList << textRect;
        m_specialTextStringList << text;
        m_specialTextTypeList << textType;
        left += textWidth;
        //Log("[CListWidgetItem::CountTextRect]: text = %s", text.toStdString().c_str());
        return;
    }
    int tempWidth = 0;
    int index = 0;
    for (int i = 0; i>=0 && i < text.count(); i++)
    {
        tempWidth += fontMetrics.width(text.at(i), 1);
        if (tempWidth >= rect.width())
        {
            QString tempText = "";
            if(tempWidth >rect.width() )
            {
                tempWidth -= fontMetrics.width(text.at(i), 1);
                i--;
            }
             tempText =     text.mid(index, i-index);
             if(fontMetrics.width(tempText) > rect.width())
             {
                 i--;
                 tempText =     text.mid(index, i-index);
             }
            QRect textRect(left+rect.left(), top, rect.width(), fontHeight);
            m_specialTextRectList << textRect;
            m_specialTextStringList << tempText;
            m_specialTextTypeList << textType;
            top += fontHeight;
           // Log("[CListWidgetItem::CountTextRect]: tempText = %s,tempWidth=%d,textRect=%d,w = %d", tempText.toStdString().c_str(),tempWidth,textRect.width(),fontMetrics.width(tempText));
            tempWidth = 0;
            index = i;
        }
    }
    if (index != text.count())
    {
        QString remainderText = text.right(text.count() - index);
        QRect textRect(left+rect.left(), top, fontMetrics.width(remainderText) + 5, fontHeight);
        m_specialTextRectList << textRect;
        m_specialTextStringList << remainderText;
        m_specialTextTypeList << textType;
        left += fontMetrics.width(remainderText) + 5;
        //Log("[CListWidgetItem::CountTextRect]: remainderText = %s", remainderText.toStdString().c_str());
    }
}
