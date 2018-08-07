#ifndef DEVICELISTVIEW_H
#define DEVICELISTVIEW_H

#include <QWidget>
#include "HMIWidgets/CAppButton.h"
#include "app_list_interface.h"

using namespace hmisdk;

class CDeviceListView : public QWidget {
    Q_OBJECT

public:
    explicit CDeviceListView(AppListInterface *pList, QWidget *parent = 0);
    ~CDeviceListView();

    void InsertDevice(int index, std::string DeviceId, QString text, QString on, QString off, bool bPaint = false);
    void DeleteDevice(int index);

protected:
    virtual void showEvent(QShowEvent *e);

signals:

public slots:
    void onDeviceSelected(std::string strId);

private:
    void ClearDeviceList();

private:
    QList<CAppButton *> m_pDevices;

    AppListInterface *m_pList;

    int m_AppWidth;
    int m_AppHeight;

    QWidget *m_pAppListArea;
};

#endif // DEVICELISTVIEW_H
