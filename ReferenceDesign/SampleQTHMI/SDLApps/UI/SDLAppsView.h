#ifndef SDLAPPSVIEW_H
#define SDLAPPSVIEW_H

#include <QWidget>
#include <QLabel>
#include "app_list_interface.h"
#include "HMIFrameWork/CView.h"

using namespace hmisdk;

class SDLAppsView : public QWidget,public CView{
    Q_OBJECT

public:
    explicit SDLAppsView(AppListInterface *pList, QWidget *parent = 0);
    ~SDLAppsView();
    virtual void viewAction(int state);

    QWidget *CenterWidget();

    // add by fanqiang
    void SetSDLStatus(bool bConnect);

    void HideAllComponent();
    void ShowAllComponent();
    void HideMenuBar();
    void ShowMenuBar();

signals:

public slots:

private:
    QWidget *m_pCenter;
    AppListInterface *m_pList;
    bool m_bInVideoStream;
    bool m_bsdlStatus;
};

#endif // SDLAPPSVIEW_H
