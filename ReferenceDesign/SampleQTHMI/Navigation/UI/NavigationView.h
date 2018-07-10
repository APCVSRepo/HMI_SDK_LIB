#ifndef NAVIGATIONVIEW_H
#define NAVIGATIONVIEW_H

#include <QWidget>
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/AppListWidget.h"

class NavigationView : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit NavigationView(QWidget *parent = 0);
    ~NavigationView();

    //CView interface
    virtual void viewAction(int state);
signals:

public slots:
    void OnConnectBtnClicked();
    void OnAppListUpdate();
    void OnAppSelected(int id);

private:
    QLabel *m_pNoDeviceMsg;
    CPushButton *m_pConnectDevice;

    AppListWidget *m_pAppList;
};

#endif // NAVIGATIONVIEW_H
