#ifndef GRAPHICWITHTEXTSHOW_H
#define GRAPHICWITHTEXTSHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/TopNavigateWidget.h"

#define RIGHT_BTN_NUM 5
#define SHOW_LINE_NUM 3
class CGraphicWithTextShow: public QWidget {
    Q_OBJECT

public:
    explicit CGraphicWithTextShow(AppListInterface *pList, QWidget *parent = 0);

    void SetAppName(QString strName);

protected:
    virtual void showEvent(QShowEvent *e);

public slots:
    void BtnMenuClickedSlots();
    void BtnBackClickedSlots();


private:
    AppListInterface *m_pList;

    //navigate item
    TopNavigateWidget *m_pTopWidget;
    //textfield
    QLabel m_aShowLine[SHOW_LINE_NUM];

    //graphic
    QLabel *m_pFrameLab;
    QLabel *m_pMusicPicLab;
};

#endif // GRAPHICWITHTEXTSHOW_H
