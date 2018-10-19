#ifndef DOUBLEGRAPHICSOFTBUTTONSSHOW_H
#define DOUBLEGRAPHICSOFTBUTTONSSHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/AlbumCoverWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CSlider.h"
#include "HMIWidgets/TopNavigateWidget.h"

class CDoubleGraphicSoftbuttonsShow : public QWidget {
    Q_OBJECT

public:
    explicit CDoubleGraphicSoftbuttonsShow(AppListInterface *pList, QWidget *parent = 0);
    ~CDoubleGraphicSoftbuttonsShow();
    void SetAppName(QString strName);
    void DeleteButton(int index);
    void removeAllButton();

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

    int m_btnWidth;
    int m_btnHeight;
    int m_btnTop;
    int m_btnLeft;
    int m_btnXSpace;
    int m_btnYSpace;

    //Graphic
    QLabel *m_pGraphicFrame;
    QLabel *m_pGraphic;
    QLabel *m_pSecGraphic;

    //softbutton
    QWidget *m_pRightArea;
    std::vector <SSoftButton> m_vSoftButtons;
    QList<CPushButton *> m_lSoftButtons;

    //navigate item
    TopNavigateWidget *m_pTopWidget;
};

#endif // DOUBLEGRAPHICSOFTBUTTONSSHOW_H
