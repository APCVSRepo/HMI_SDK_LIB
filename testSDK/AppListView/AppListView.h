#ifndef APPLISTVIEW_H
#define APPLISTVIEW_H

#include <QWidget>
#include "CAppButton.h"
#include "AppListInterface.h"
//#include "UI/Common/AppBase.h"

class CAppListView : public QWidget
{
    Q_OBJECT
public:
    explicit CAppListView(AppListInterface * pList,QWidget *parent = 0);
    ~CAppListView();

    void InsertChildApp(int index,int funcId,QString text,QString on,QString off,bool bPaint = false);
    void DeleteChildApp(int index);
protected:
    virtual void showEvent(QShowEvent * e);
signals:

public slots:
    void onChildAppSelected(int funcId);

private:
    QList<CAppButton*> m_pChildApps;

    AppListInterface *m_pList;

    int m_AppWidth;
    int m_AppHeight;
};

#endif // APPLISTVIEW_H
