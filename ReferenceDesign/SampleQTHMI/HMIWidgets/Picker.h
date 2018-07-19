#ifndef PICKER_H
#define PICKER_H

#include <QListWidget>
#include <QColor>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QMap>
class Picker : public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue);
public:
    enum eFontStyle
    {
        eDefaultFontStyle,
        eToRightSmallIStyle,
        eToLeftSmallIStyle,
        eToRightBigIStyle,
        eToLeftBigIStyle
    };
    enum ePickType
    {
        EPickTypeKnown,
        EPickTypeYear,
        EPickTypeMonth,
        EPickTypeDay,
        EPickTypeHour,
        EPickTypeMin,
        EPickTypeAmAndPm
    };
    struct SPositionHandle
    {
      int    i_row;
      double d_xMove;
      double d_yMove;
      double d_xZoom;
      double d_yZoom;
    };
    explicit Picker(QWidget *parent = 0);
    ~Picker();
    void InsertItem(int index, const QString &text, const QSize& itemSize, int fontSize, int specifiedID = -1);
    void SetFontStyle(eFontStyle type);
    void SetCircular(bool mode);
    eFontStyle GetFontStyle();
    QString GetItemText(int index);
    int GetItemSpecifiedID(int index);
    void SetItemCountPerPage(int count);
    int getItemCountPerPage();
    void UpdateItemText(int index, const QString& qsText);
    void SetCurrentIndex(int index);

    void SetReleaseIndex(int index);
    int getReleaseIndex();

    void SetIsRelease(bool is);
    bool getIsRelease();

    void SetCurrentFontSize(int fontSize);
    int getCurrentFontSize();
    int getCurrentIndex();
    int getCount();
    void SetPickerEnabel(bool isEnabel);
    bool GetPickerEnabel();
    void SetCurColor(QColor& color);
    QColor getCurColor();
    void SetTextAlpha(qreal transparent);
    void SetUpAndDownColor(QColor& color);
    QColor getUpAndDownColor();
    void setAlPha(qreal al);
    void setPickerMaximum(int max);
    void setPickerMinimum(int min);
    void PickerRebound(int startValue ,int endValue);
    void StopPickerRebound();
    int value() const;
    void setValue(const int value);
    void setIsAnimation(bool is);
    QSize getItemSize();
    void setName(QString);
    QString getName();
    void setPickerPositionHandle(double xmove,double ymove,double xzoom,double yzoom,int nrow);
    QMap<int,Picker::SPositionHandle> getPositionHandle();
    bool getIsAnimatonEnd();
    void setPickType(ePickType type);
protected:
    bool eventFilter(QObject *object, QEvent *event);
    bool MouseEvent(QObject *object, QEvent *event);
signals:
    void currentIndexChanged(int index);
    void updateYear(int step,int index);
    void updateAmOrPm(int upOrDown,int index);
    void pressIndex(int index);
    void PaintEnd(QString name);
    void pickerEnd(int);
public slots:
    void PaintFinish();
private:
    int            m_nMouseDownX;
    int            m_nMouseDownY;
    int            m_nLastScrollBarValue;
    bool           m_bCircularList;
    bool           DragDiraction;
    QSize          m_sizeItem;
    int            m_nItemCountPerPage;
    int            m_currentIndex;
    int            m_releaseIndex;
    int            m_nCurrentFontSize;
    eFontStyle     m_FontStyle;
    bool           m_isPickerEnable;
    QColor         m_curColor;
    QColor         m_Color;
    qreal          m_alph;
    int            m_maxMum;
    int            m_minMum;
    bool           m_isSetMaxMum;
    bool           m_isSetMinMum;
    QPropertyAnimation *m_am;
    bool           m_isPickerAnimation;
    bool           m_isrealse;
    QString        m_name;
    Picker::SPositionHandle m_PosionHandle;
    QMap<int,Picker::SPositionHandle> m_PosionHandleMap;
    bool           m_AnimationIsEnd;
    ePickType      m_pickType;
};

#endif // PICKER_H
