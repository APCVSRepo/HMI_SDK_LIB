#ifndef SETTINGSWIFIPASSWORDUI_H
#define SETTINGSWIFIPASSWORDUI_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsWifiPasswordUI : public QWidget , public CView
{
    Q_OBJECT
public:
    explicit SettingsWifiPasswordUI(QWidget *parent = 0);
    ~SettingsWifiPasswordUI();
    virtual void viewAction(int state);
signals:

public slots:
    void OnBack();
    void OnConnectBtnClicked();
    void OnCancelBtnClicked();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);

private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;

    QLabel *m_pPasswordLabel;
    QLineEdit *m_pPasswordEdit;
    QLabel *m_pPasswordEditLine;
    QLabel *m_pPasswordError;

    QPushButton *m_pConnectBtn;
    QPushButton *m_pCancelBtn;
};

#endif // SETTINGSWIFIPASSWORDUI_H
