#ifndef LARGERAPHICONLYSHOW_H
#define LARGERAPHICONLYSHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/AlbumCoverWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CSlider.h"
#include "HMIWidgets/TopNavigateWidget.h"

class CLargeGraphicOnlyShow : public QWidget {
    Q_OBJECT

public:
    explicit CLargeGraphicOnlyShow(AppListInterface *pList, QWidget *parent = 0);
    ~CLargeGraphicOnlyShow();
    void SetAppName(QString strName);
    void DeleteButton(int index);
    void removeAllButton();

protected:
    void showEvent(QShowEvent *e);
public slots:

    void BtnMenuClickedSlots();
    void BtnBackClickedSlots();

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

    //navigate item
    TopNavigateWidget *m_pTopWidget;
};

#endif // LARGERAPHICONLYSHOW_H
