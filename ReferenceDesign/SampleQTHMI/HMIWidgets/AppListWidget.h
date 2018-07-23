#ifndef APPLISTWIDGET_H
#define APPLISTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "CAppButton.h"

class AppListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppListWidget(QWidget *parent = 0);
    ~AppListWidget();

    void InsertChildApp(int index, int funcId, QString text, QString on, QString off, bool bPaint = false);
    void RemoveAll();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
protected:
    virtual void showEvent(QShowEvent *e);
private:
    void UpdateItemShow(unsigned int iStartItemIndex = 0);
    void DeleteChildApp(int index);

signals:
    void appSelected(int id);

public slots:
    void onChildAppSelected(int funcId);

private:
    QList<CAppButton *> m_pChildApps;

    int m_AppWidth;
    int m_AppHeight;

    int m_pressx;
    int m_pressy;
    int m_curpage;

    QWidget *m_pAppListArea;
};

#endif // APPLISTWIDGET_H
