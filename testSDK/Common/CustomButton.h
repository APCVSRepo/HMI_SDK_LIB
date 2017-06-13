#ifndef CCUSTOMBUTTON_H
#define CCUSTOMBUTTON_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <string>

std::string ChangeSlash(std::string strSrc);

class CCustomButton : public QWidget
{
    Q_OBJECT
public:
    explicit CCustomButton(QWidget *parent = 0);
    ~CCustomButton();

    enum BtnStatus{BTN_STAT_NORMAL = 0,BTN_STAT_PRESSED,BTN_STAT_HOVER};

    void SetTextStyle(std::string strQtStyle);
    void SetText(std::string strText,int iAlign = Qt::AlignCenter);
    std::string Text();
    void SetBackPicPath(std::string strNormalPic,std::string strPressPic = "",std::string strHoverPic = "");
    void SetLeftIcon(std::string strIcon);
    void SetRightIcon(std::string strIcon);
    void SetSize(int iWidth, int iHeight);
    void SetPadding(int iPadding);
    void SetPadding(int iLeft,int iTop,int iRight,int iBottom);
    void Init(int iWidth,int iHeight,std::string strtext,std::string strNormalPic,std::string strPressPic = "",std::string strHoverPic = "");

    void SetId(int iId);
    void SetCustomName(std::string strName);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void Clicked();
    void Clicked(int id);
    void Clicked(int iId,std::string strName);
    void ClickedLong();
    void ClickedLong(int id);
public slots:
    void CheckHoverSlot();
private:
    void SetBackImage(int iState = BTN_STAT_NORMAL);
    int m_iOldState;
    std::string m_strNormalPicPath;
    std::string m_strPressPicPath;
    std::string m_strHoverPicPath;

    QHBoxLayout *m_pMainLayout;
    QLabel *m_pLeftIconLab;
    QLabel *m_pTextLab;
    QLabel *m_pRightIconLab;

    QPoint m_point;
    QTime m_pressedTime;
    QTimer *m_pCheckHoverTimer;

    std::string m_Text;
    int m_iId;
    std::string m_strCustomName;
};

#endif // CCUSTOMBUTTON_H
