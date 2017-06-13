#ifndef CBUTTON_H
#define CBUTTON_H

//#include "UI/UIInclude.h"
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QTime>
#include <string>

class CButton : public QWidget
{
    Q_OBJECT
public:
    explicit CButton(QWidget *parent = 0);
    CButton(int W, int H, QString normalIcon = NULL, QString pressedIcon = NULL, QString disableIcon = NULL);
    ~CButton();

    enum BtnStatus
    {
        BTN_STAT_UNKNOW = 0,
        BTN_STAT_NORMAL,
        BTN_STAT_PRESSED,
        BTN_STAT_DISABLE
    };

    void initParameter(int W, int H, QString normalIcon, QString pressedIcon, QString disableIcon = "", QString text = "");
    void setId(int id);
    void SetCustomName(std::string strName);
    void setSize(int W, int H);
    void setIconNormal(QString imagePath, bool flag = true);
    void setIconPressed(QString imagePath, bool flag = true);
    void setIconDisable(QString imagePath, bool flag = true);
    void setIconExtra(QString imagePath);
    void setText(QString text, bool flag = true);
    void setTextStyle(QString style, bool flag = true);
    void changeToNormal();
    void changeToPressed();
    void changeToDisable();
    void changeToExtra(bool flag = true);
    void updateText();
    void updateTextStyle();
    bool isNormal();
    bool isPressed();
    bool isDisable();

    void SetLeftIcon(QString strIconPath);
signals:
    void clicked();
    void clicked(int id);
    void clicked(int iId,std::string strName);

    void clickedLong();
    void clickedLong(int id);
public slots:

private:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QLabel m_IconLabel;
    QLabel m_IconLabelExtra;
    QLabel m_TextLabel;
    QString m_IconNormalPath;
    QString m_IconPressedPath;
    QString m_IconDisablePath;
    QString m_IconExtraPath;
    QString m_Text;
    QString m_Style;

    QHBoxLayout *m_pMainLayout;
    QVBoxLayout *m_pIconLayout;
    QVBoxLayout *m_pTextLayout;
    QLabel *m_pLeftIconLab;

    int m_Id;
    std::string m_strCustomName;

    int m_BtnStatus;
    int m_i_clickX;
    int m_i_clickY;

    unsigned int m_i_time;

    bool m_bLeftIcon;
    int GetTextWidth();
};
#endif // CBUTTON_H
