#ifndef CVLISTWIDGET_H
#define CVLISTWIDGET_H

#include <QListWidget>
#include "ListScroller.h"
#include "CListWidgetItem.h"
#include "ScrollText.h"
#include "CComboBox.h"
class CVListWidget : public QListWidget
{
    Q_OBJECT
public:
    enum eButtonPushStyle{
        ePushStyle_UnKnow,
        ePushStyle_Alpha
    };
    explicit CVListWidget(QWidget *parent = 0);
    ~CVListWidget();

    void InsertItem(int index, CListWidgetItem *item);
    void InsertItem(int index, const CListWidgetItem& item);
    void RemoveItem(int index);
    void RemoveItems(int start, int end);
    void RemoveAllItems(bool bRemoveCursorIndex = true);
    void UpdateItemText(int index, const QString& text, int nTextIndexInItem = 0);

    QString GetItemText(int index, int nTextIndexInItem) const;

    void SetIndicator(const QRect& rect, const QString &qsIndicatorPath);
    void SetIndicatorIndex(int index, bool bAutoScrollCursoredItem = true);
    void SetItemBackgroundInfo(const QString &qsNormalPath,
                               const QString &qsPressedPath,
                               const QString &qsCursoredPath);

    void SetSplitLine(const QString &qsOutLinePath, const QString& qsInLinePath);
    void SetSplitLineForPhoneApp(const QString &qsLine); //for Phone app
    bool IsDrawingSplitLine();
    bool IsDrawingSplitLineForPhoneApp();

    void SetScrollBarStyleSheet(int nScrollBarWidth, int nHandleWidth);
    void SetSpacing(int space);
    void AutoSetSelected(bool state);
    void AutoScrollCursoredItem(bool state);
    void SetIndicatorState(bool state); //true: show; false: hide
    void AddComboBox(int index,const QString& icon,const QStringList& listtext, const QRect& comboboxrect,const QSize& itemsize);

    void SetCursor(int index);
    void SetItemSelected(int index);
    int GetIndexBySpecifiedID(int specifiedID);
    int GetSpecifiedID(int index);
    int GetSpecifiedIDStatus(int index);
    unsigned long long GetSpecifiedTrackID(int index);
    QString GetSpecifiedText(int index);
    QString GetSpecifiedText2(int index);
    bool IsElidedTextEnabled();

    void SetItemTextColor(int index, unsigned int nIndexInItem, const QColor& color);
    void SetItemTextSize(int index, unsigned int nIndexInItem, const int fontSize);
    void SetItemIconPixmap(int index, unsigned int nIndexInItem, const QPixmap& pixmap);
    void SetItemIconShowHide(int index, unsigned int nIndexInItem, bool bShow);
    void SetItemButtonPixmap(int index, unsigned int nIndexInItem, const QStringList pathList);
    void SetItemFontSize(int fontSize);
    void SetItemDisabled(int index, bool disabled);
    void SetItemButtonDisabled(int index, unsigned int nBtnNumber, bool disabled);
    void SetSpecifiedID(int index, int id);
    void SetSpecifiedIDStatus(int index, int status);
    void SetSpecifiedText(int index, QString text);
    void SetSpecifiedText2(int index, QString text);
    void SetElidedTextEnabled(bool flag);
    void SetItemCheckBoxState(int index, bool bChecked);
    void SetItemCheckBoxDisabled(bool mode);
    void ClearCheckBoxState();
    void SetItemSelectedTextIndex(int index);

    void SetLeftMargin(int margin);
    int  GetLeftMargin();

    void PressedEventAction(const QPoint& pos);
    void MovedEventAction();
    void ReleasedEventAction(const QPoint& pos);

    inline int GetPressedIndex()   { return m_nPressedIdx; }
    inline int GetCursorIndex()    { return m_nCursorIdx; }
    inline int GetSelectedIndex()  { return m_nSelectedIdx; }
    inline int GetIndicatorIndex() { return m_nIndicatorIdx; }
    inline int GetSpacing()   { return m_nSpacing; }
    inline int GetItemWidth() { return m_itemSize.width(); }

    inline QImage  GetItemNormalImage()     { return m_imageItemNormal; }
    inline QPixmap GetItemPressededPixmap() { return m_pixmapItemPressed; }

    inline QPixmap GetItemCursoredPixmap() { return m_pixmapItemCursored; }
    inline QImage  GetOutSplitLineImage()  { return m_imageOutSplitLine; }
    inline QImage  GetInSplitLineImage()   { return m_imageInSplitLine; }
    inline QImage  GetSplitLineImageForPhoneApp() { return m_imageSplitLineForPhoneApp; }

    inline QRect   GetIndicatorRect()   { return m_rectIndicator; }
    inline QPixmap GetIndicatorPixamp() { return m_pixmapIndicator; }

    inline bool GetIndicatorState() { return m_bDrawIndicator; }

    void setGeometry(int x, int y, int w, int h);
    void setGeometry(const QRect & rect);

    void ProcessScrollText(QPainter *painter, int x, int y);
    void SetItemTop(int index);
    void SetItemBottom(int index);
    void SetSpecialStyle();
    void SetTopItemChanged();
    void SetTopItemChanged(int value);
    void SetScrollBarStyle(int nScrollBarWidth);

    void SetButtonPushStyle(eButtonPushStyle style);
    eButtonPushStyle getButtonPushStyle();
public slots:
    void setEnabled(bool mode);
    void setDisabled(bool mode);

private:
    void InitListWidget();
    bool IsCursored(int index);
    int  IsButtonPushed(QListWidgetItem* pItem, const QPoint& pos);
    int  IsCheckBoxPushed(QListWidgetItem* pItem, const QPoint& pos);
    QString IsHighlightText(QListWidgetItem* pItem, const QPoint& pos, int& highlightTextType);
    QString GetHighlightText(const QStringList& qsList);
    void SetScrollBarStyle1(int nScrollBarWidth);
    void SetScrollBarStyle2(int nScrollBarWidth);
    void SetScrollBarStyle3(int nScrollBarWidth);
    QDate GetDateFromString(const QStringList& qsList);
    QTime GetTimeFromString(const QStringList& qsList);
    void RecoverButtonState(QListWidgetItem* pItem);
    //
    bool IsItemDisabled(QListWidgetItem* pItem);
public slots:
   void OnComboBoxActivated(int ComboBoxIndex ,const QString &data);
   void OnComboBoxActivated(int ComboBoxIndex ,int itemIndex);
signals:
    void listItemClicked(int index);
    void listItemReleased(int index);
    void listItemReleased(int index, int specifiedID);
    void phoneNumberReleased(const QString& qsNumber);
    void dateTimeReleased(const QString& qsDateTime);
    void dateTimeReleased(const QDateTime& dateTime);

    void listButtonClicked(int index, int btnIndex);
    void listButtonReleased(int index, int btnIndex);
    void listButtonReleased(int index, int btnIndex, int specifiedID);
    void listCheckBoxReleased(int index, bool bChecked);
    void topItemChanged(int index);

    void ComboBoxActivated(int ComboBoxIndex ,const QString &data);
    void ComboBoxActivated(int ComboBoxIndex ,int itemIndex);
private:
    ListScroller* m_pScroller;
    ScrollText*   m_pScrollText;
    QListWidgetItem* m_pPressedItem; //add for remove button state
    //
    QRect            m_rectIndicator;
    QSize            m_itemSize;
    QColor           m_colorNormal;
    QColor           m_colorSelected;
    QColor           m_colorDisabled;
    QPoint           m_pointPressed;
    //
    QImage           m_imageItemNormal;
    QPixmap          m_pixmapItemPressed;
    QPixmap          m_pixmapItemCursored;
    QPixmap          m_pixmapIndicator;
    //
    QImage           m_imageOutSplitLine;
    QImage           m_imageInSplitLine;
    QImage           m_imageSplitLineForPhoneApp;
    //
    QList<QListWidgetItem*>    m_listCheckedItem;
    //
    int              m_nCursorIdx;
    int              m_nIndicatorIdx;
    int              m_nPressedIdx;
    int              m_nFontPixelSize;
    int              m_nPressedButtonIdx;
    int              m_nPressedCheckBoxIdx;
    int              m_nSpacing;
    int              m_nLeftMargin;
    int              m_nItemSelectedIndex;
    int              m_nSelectedIdx;
    //
    bool             m_bDrawSplitLine;
    bool             m_bDrawSplitLineForPhoneApp;
    bool             m_bAutoSetSelected;
    bool             m_bAutoScrollCursoredItem;
    bool             m_bDrawIndicator;
    bool             m_bElidedTextEnabled;
    bool             m_bAutoResizeGeometry;
    bool             m_bCheckBoxDisabled;
    eButtonPushStyle m_eBtnPushStyle;
};

#endif // CVLISTWIDGET_H
