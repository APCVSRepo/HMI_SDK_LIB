#ifndef APPLISTVIEW_H
#define APPLISTVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include "CAppButton.h"
#include "app_list_interface.h"

class CAppListView : public QWidget {
  Q_OBJECT
 public:
  explicit CAppListView(AppListInterface *pList, QWidget *parent = 0);
  ~CAppListView();

  void InsertChildApp(int index, int funcId, QString text, QString on, QString off, bool bPaint = false);
  void DeleteChildApp(int index);

  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
 protected:
  virtual void showEvent(QShowEvent *e);
 private:
  void UpdateItemShow(unsigned int iStartItemIndex = 0);

 signals:

 public slots:
  void onChildAppSelected(int funcId);

 private:
  QList<CAppButton *> m_pChildApps;

  AppListInterface *m_pList;

  int m_AppWidth;
  int m_AppHeight;

  int m_pressx;
  int m_pressy;
  int m_curpage;
};

#endif // APPLISTVIEW_H
