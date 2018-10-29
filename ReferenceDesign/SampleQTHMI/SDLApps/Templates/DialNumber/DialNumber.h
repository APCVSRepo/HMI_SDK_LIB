#ifndef DIALNUMBER_H
#define DIALNUMBER_H

#include <QWidget>
#include <QString>
#include "SDLApps/Templates/Common/AppBase.h"

class CDialNumber : public QWidget
{
    Q_OBJECT
public:
    explicit CDialNumber(AppListInterface *pList, QWidget *parent = 0);

signals:

public slots:
    //AudioPassThru popup
    void OnDialNumberCall();
    void OnDialNumberCancel();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    //DialNumber popup
    void ShowPopupDialNumber(const QString &appName, const QString &dialNumber);
    void HidePopupDialNumber();

private:
    AppListInterface *m_pList;
    bool m_bShowPopUpDialNumber;
    QString m_dialNumber;
};

#endif // DIALNUMBER_H
