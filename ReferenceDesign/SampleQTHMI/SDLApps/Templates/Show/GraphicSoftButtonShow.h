#ifndef GRAPHICSOFTBUTTONSHOW_H
#define GRAPHICSOFTBUTTONSHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/TopNavigateWidget.h"

#define RIGHT_BTN_NUM 5

class CGraphicSoftButtonShow : public QWidget {
    Q_OBJECT

public:
    explicit CGraphicSoftButtonShow(AppListInterface *pList, QWidget *parent = 0);

    void SetAppName(QString strName);

protected:
    virtual void showEvent(QShowEvent *e);

public slots:
    void SoftBtnClickedSlot(int iSoftBtnID);
    void BtnMenuClickedSlots();

private:
    void setSoftButtons(std::vector<SSoftButton> vec_softButtons);

private:
    AppListInterface *m_pList;

    //navigate item
    TopNavigateWidget *m_pTopWidget;

    //softbutton
    QWidget *m_pRightArea;
    std::vector <SSoftButton> m_vSoftButtons;
    CButton m_aSoftBtn[RIGHT_BTN_NUM];

    //graphic
    QLabel *m_pMusicPicLab;
};

#endif // GRAPHICSOFTBUTTONSHOW_H
