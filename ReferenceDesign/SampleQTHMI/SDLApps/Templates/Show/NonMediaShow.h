#ifndef NONMEDIASHOW_H
#define NONMEDIASHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/AlbumCoverWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CSlider.h"
#include "HMIWidgets/TopNavigateWidget.h"

#define RIGHT_BTN_NUM 5
#define SHOW_LINE_NUM 3

class CNonMediaShow : public QWidget {
    Q_OBJECT

public:
    explicit CNonMediaShow(AppListInterface *pList, QWidget *parent = 0);
    ~CNonMediaShow();
    void SetAppName(QString strName);

    // QWidget interface
protected:
    void showEvent(QShowEvent *e);
public slots:

    void BtnMenuClickedSlots();
    void BtnBackClickedSlots();

    void SoftBtnClickedSlot(int iSoftBtnID);

private:
    void setSoftButtons(std::vector<SSoftButton> vec_softButtons);

private:
    AppListInterface *m_pList;
    //background
    QLabel *m_pBackground;

    //album
    QLabel *m_pFrameLab;
    QLabel *m_pAlbumCover;

    //right softbutton
    QWidget *m_pRightArea;
    std::vector <SSoftButton> m_vSoftButtons;
    CButton m_aSoftBtn[RIGHT_BTN_NUM];

    //navigate item
    TopNavigateWidget *m_pTopWidget;

    //textfield
    QLabel m_aShowLine[SHOW_LINE_NUM];
};

#endif // NONMEDIASHOW_H
