#ifndef TEXTANDSOFTBUTTONSWITHGRAPHICSHOW_H
#define TEXTANDSOFTBUTTONSWITHGRAPHICSHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/AlbumCoverWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CSlider.h"
#include "HMIWidgets/TopNavigateWidget.h"

#define RIGHT_BTN_NUM 5
#define SHOW_LINE_NUM 3

class CTextAndSoftbuttonsWithGraphicShow : public QWidget {
    Q_OBJECT

public:
    explicit CTextAndSoftbuttonsWithGraphicShow(AppListInterface *pList, QWidget *parent = 0);
    ~CTextAndSoftbuttonsWithGraphicShow();
    void SetAppName(QString strName);

    void DeleteButton(int index);
    void removeAllButton();
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
    int m_btnWidth;
    int m_btnHeight;
    int m_btnTop;
    int m_btnLeft;
    int m_btnXSpace;
    int m_btnYSpace;

    //Graphic
    QLabel *m_pGraphicFrame;
    QLabel *m_pGraphic;
    std::vector <SSoftButton> m_vSoftButtons;
    QList<CPushButton *> m_lSoftButtons;

    //navigate item
    TopNavigateWidget *m_pTopWidget;

    //textfield
    QLabel m_aShowLine[SHOW_LINE_NUM];
};

#endif // TEXTANDSOFTBUTTONSWITHGRAPHICSHOW_H
