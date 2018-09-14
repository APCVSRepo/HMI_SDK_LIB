#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QGraphicsOpacityEffect>
#include <QPaintEvent>
#include <QTimer>
class CPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum eStatus{
        eStatus_Normal,
        eStatus_Push,
        eStatus_Select
    };
    explicit CPushButton(QWidget *parent = 0);
    void SetStyle(const QString& style);

    bool event(QEvent *e);
    void SetType(const QString& type );
    void SetStatus(eStatus status);
    void SetId(int id);
    void SetData(const QString& data );
    void SetStatusStyle(const QRect& rect,const QString& normal ,const QString& push ,const QString& select);
    void SetEnabled(bool isEnabeled);

    QString GetType();
    eStatus GetStatus();
    QString GetData();
    int GetId();
    void SetIcon(const QRect& rect,const QString& icon);
    void SetText(const QRect &rect, const QString& text,int fontsize = 24,Qt::Alignment align = Qt::AlignCenter,const QColor &color = QColor(255,255,255));
    void SetEffect(double effect);
    void SetEnableEffect(bool isEnable);


protected:
    void MouseEvent(QEvent *e);
    void paintEvent(QPaintEvent *e);

public: signals:
    void LongPress();
    void clicked(int id);
public slots:
    void OnLongPressTotal();
    void OnLongPress();
    void OnClicked();
private:
    QGraphicsOpacityEffect* m_pEffect;
    QString m_type;
    eStatus m_status;
    int m_iId;
    QString m_data;
    QString m_icon;
    QRect m_iconRect;
    Qt::Alignment m_iconAlign;

    QString m_text;
    QRect m_textRect;
    int m_textFontSize;
    QColor m_textColor;
    Qt::Alignment m_textAlign;

    QTimer m_LongPressTotalTimer;
    QTimer m_LongPressTimer;

    bool m_bIsEnabled;
    double m_dEffect;
    bool m_bEnableEffect;
    eStatus m_eBtnStatus;
    QString m_btnNormalStyle;
    QString m_btnPushStyle;
    QString m_btnSelectStyle;
    QRect m_btnStatusRect;
};

#endif // CPUSHBUTTON_H
