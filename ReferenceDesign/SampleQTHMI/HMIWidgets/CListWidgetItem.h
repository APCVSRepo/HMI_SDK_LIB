#ifndef CLISTWIDGETITEM_H
#define CLISTWIDGETITEM_H

#include <QWidget>
#include <QVariantList>

class CListWidgetItem
{
public:
    enum eButtonState {
        eNormalState = 0,
        ePressedState,
        eSelectedState,
        eDisabledState
    };
    enum eItemDataRole
    {
        eBackgroundMode = Qt::UserRole+1,
        eTextRectMode,
        eTextStringMode,
        eTextAlignMode,
        eTextColorMode,
        eTextSizeMode,
        eTextTypeMode,
        eSpecialTextStringMode,
        eSpecialTextRectMode,
        eSpecialTextTypeMode,
        eSpecialTextBackgroundRectMode,
        eSpecialTextBackgroundIconMode,
        eIconRectMode,
        eIconPixmapMode,
        eIconIndicatorMode,
        eIconShowHideMode,
        eButtonRectMode,
        eButtonPixmapMode,
        eButtonStateMode,
        eButtonIndicatorMode,
        eButtonBgDrawMode,
        eCheckBoxRectMode,
        eCheckBoxPixmapBgMode,
        eCheckBoxPixmapCheckMode,
        eCheckBoxStateMode,
        eIndicatorMode,
        eSpanNameMode,
        eSpecifiedIDMode,
        eSpecifiedIDStatusMode,
        eSpecifiedIDNumMode,
        eSpecifiedIDNum2Mode,
        eTrackIDMode,
        eTitleNameMode,
        eDisabledMode
    };

    CListWidgetItem();
    CListWidgetItem(const QSize& sizeBg);
    ~CListWidgetItem();

    void SetBackgroundInfo(const QString &qsNormalPath,
                           const QString &qsPressedPath,
                           const QString &qsCursoredPath);
    void AddText(const QRect& rect, const QString& text, int flags = Qt::AlignVCenter, int fontSize = 26, QColor color=QColor(255,255,255));
    void AddSpecialText(const QRect& rect, const QString& text, int flags = Qt::AlignVCenter, int fontSize = 26, QColor color=QColor(255,255,255),bool addBackground = false,QColor backgroundColor = QColor(46,46,46,107));
    void AddIcon(const QRect& rect, const QPixmap& pixmap, bool bIndicator = false, bool bShow = true);

    //mode=1: PressedBg will replace NormalBg; mode=0: PressedBg will draw under NormalBg
    void AddButton(const QRect& rect, const QStringList pathList,
                   eButtonState state = eNormalState, bool bIndicator = false, int mode = 0);

    void AddCheckBox(const QRect& rect, const QPixmap& pixmapBg, const QPixmap& pixmapCheck, bool bChecked = false);
    void SetSpecifiedID(int id);
    void SetSpecifiedIDStatus(int Status);
    void SetSpecifiedTrackID(unsigned long long id);
    void SetSpecifiedNum(QString text);
    void SetTitleName(const QString& name);

private:
    bool IsPhoneNumber(const QString& qsNumber);
    bool IsDate(QString& qsDate);
    bool IsTime(QString& qsTime);
    bool CheckHighlightText(const QString& qsText);

    void CountHighlightText(QString& text, const QRect &rect, int textType, int fontSize, int remainderWidth, int &left, int &top);
    void CountNormalText(QString& text, const QRect &rect, int textType, int fontSize, int remainderWidth, int &left, int &top);
    void CountTextRect(const QFontMetrics &fontMetrics, QString& text, const QRect &rect, int textType, int &left, int &top);

    QPixmap getRoundedRectangle(QColor color, int width, int height, int radius);

public:
    QSize          m_sizeItem;
    QStringList    m_qsListBackground;
    //--- for texts ---
    QVariantList   m_textRectList;
    QStringList    m_textStringList;
    QVariantList   m_textAlignList;
    QVariantList   m_textColorList;
    QVariantList   m_textSizeList;
    QVariantList   m_textTypeList; //true: special text; false: normal text;
    //--- for special texts ---
    QVariantList   m_specialTextRectList;
    QStringList    m_specialTextStringList;
    QVariantList   m_specialTextTypeList;
    QVariantList   m_iconRectspecialTextBackgroundList;
    QVariantList   m_iconspecialTextBackgroundList;
    //--- for icons ---
    QVariantList   m_iconRectList;
    QVariantList   m_iconPixmapList;
    QVariantList   m_iconIndicatorList;
    QVariantList   m_iconShowHideList;
    //--- for buttons ---
    QVariantList   m_buttonRectList;
    QVariantList   m_buttonPathList;
    QVariantList   m_buttonStateList;
    QVariantList   m_buttonIndicatorList;
    QVariantList   m_buttonBgDrawModeList; //true: PressedBg will replace NormalBg; false: PressedBg will draw under NormalBg
    //--- for checkboxs ---
    QVariantList   m_checkBoxRectList;
    QVariantList   m_checkBoxBgPixmapList;
    QVariantList   m_checkBoxCheckPixmapList;
    QVariantList   m_checkBoxStateList;
    //
    int            m_nSpecifiedID;
    int            m_nSpecifiedIDStatus;
    unsigned long long  m_lluSpecifiedTrackID;
    QString        m_qsPhoneNum;
    QString        m_qsTitleName;

private:
    bool             m_bMatchPhoneNumber;
    int              m_nLineSpacing;
    QStringList      m_qsListText;
    QList<int>       m_listSpecialTextType; //1:Phone Number;  2:DateTime;  3:DateTime String
};

#endif // CLISTWIDGETITEM_H
