#ifndef GRAPHICSOFTBUTTONSHOW_H
#define GRAPHICSOFTBUTTONSHOW_H

#include <QLabel>
#include <QProgressBar>
#include "Common/AppBase.h"
#include "Common/Button.h"
#include "Common/CustomButton.h"


class CGraphicSoftButtonShow : public QWidget
{
    Q_OBJECT
public:
    explicit CGraphicSoftButtonShow(AppListInterface * pList, QWidget *parent = 0);

    void SetAppName(QString strName);

protected:
    virtual void showEvent(QShowEvent * e);

public slots:
    void SoftBtnClickedSlot(int iSoftBtnID);
    void BtnMenuClickedSlots();

private:
    void setSoftButtons(std::vector<SSoftButton> vec_softButtons);

    AppListInterface *m_pList;

    QLabel *m_pAppNameLab;
    CCustomButton *m_pMenuBtn;
    QLabel *m_pMusicPicLab;
    CButton m_aSoftBtn[5];
    QHBoxLayout *m_pBtnLayout;
    QLabel m_aSplit[5];
    QLabel *m_pShadowLab;

    // softbutton容器
    std::vector <SSoftButton> m_vSoftButtons;
};

#endif // GRAPHICSOFTBUTTONSHOW_H
