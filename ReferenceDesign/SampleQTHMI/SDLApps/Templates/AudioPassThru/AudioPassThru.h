#ifndef AUDIOPASSTHRU_H
#define AUDIOPASSTHRU_H

#include <QWidget>
#include "Common/AppBase.h"

class CAudioPassThru : public QWidget {
    Q_OBJECT

public:
    explicit CAudioPassThru(AppListInterface *pList, QWidget *parent = 0);

signals:

public slots:

    // QWidget interface
protected:
    void showEvent(QShowEvent *);

private:
    AppListInterface *m_pList;
};

#endif // AUDIOPASSTHRU_H
