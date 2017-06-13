#ifndef AUDIOPASSVIEW_H
#define AUDIOPASSVIEW_H

#include <QWidget>
#include "Common/AppBase.h"

class CAudioPassView : public QWidget
{
    Q_OBJECT
public:
    explicit CAudioPassView(AppListInterface *pList,QWidget *parent = 0);

signals:

public slots:

private:
    AppListInterface *m_pList;


};

#endif // AUDIOPASSVIEW_H
