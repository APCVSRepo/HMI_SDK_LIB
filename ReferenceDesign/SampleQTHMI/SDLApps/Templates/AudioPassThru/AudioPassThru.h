#ifndef AUDIOPASSTHRU_H
#define AUDIOPASSTHRU_H

#include <QWidget>
#include <string>
#include "SDLApps/Templates/Common/AppBase.h"

using std::string;

class CAudioPassThru : public QWidget {
    Q_OBJECT

public:
    explicit CAudioPassThru(AppListInterface *pList, QWidget *parent = 0);

signals:

public slots:
    //AudioPassThru popup
    void OnAudioPassThruFinish();
    void OnAudioPassThruCancel();
    void OnAudioPassThruTimeOut();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    //AudioPassThru popup
    void ShowPopupAudioPassThru(const string &appName, const string &duration, const string &contextA);
    void HidePopupAudioPassThru();

private:
    AppListInterface *m_pList;
    bool m_bShowPopUpAudioPassThru;
};

#endif // AUDIOPASSTHRU_H
