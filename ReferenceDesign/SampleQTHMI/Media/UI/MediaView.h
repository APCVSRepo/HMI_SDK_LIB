#ifndef MEDIAVIEW_H
#define MEDIAVIEW_H

#include <QWidget>
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/AppListWidget.h"

class MediaView : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit MediaView(QWidget *parent = 0);
    ~MediaView();

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

#endif // MEDIAVIEW_H
