#ifndef SliderSelect_H
#define SliderSelect_H
#include <QWidget>
#include <QMap>
#include <QMouseEvent>
#include <QTouchEvent>
#include <QLabel>
#include <QPainter>

class SliderSelect:public QWidget
{
    Q_OBJECT
public:

    enum eViewStatus
    {
        eUnknow,
        eNormal,
        ePushed,
        eSelect
    };
    explicit SliderSelect(QWidget *parent = NULL);
    ~SliderSelect();

    void SetGeometry(QRect rect);
    void SetNormalStyle(QString style);
    void SetPushStyle(QString style);
    void SetSelectStyle(QString style);
    void SetPosionID(int id);
    int GetPosionID();
    void Insert(int index);
    void setRect(QRect rect);
    QRect getRect();
    void setIndex(int index);
    int getIndex();
    void setSize(QSize size);
    QSize getSize();
    void setText(QString &text);
    void setViewRect(QRect &rect);
    QRect getViewRect();
    void setStatus(eViewStatus status);
    void UpdateStatus(eViewStatus status);
    eViewStatus getStatus();

protected:
    void paintEvent(QPaintEvent *event);
private:
   QString m_normalStyle;
   QString m_pushStyle;
   QString m_selectStyle;
   QString m_text;
   int m_iIndex;
   int m_iPosionId;
   QRect m_rect;
   QSize  m_size;
   eViewStatus m_status;
};

#endif // SliderSelect_H
