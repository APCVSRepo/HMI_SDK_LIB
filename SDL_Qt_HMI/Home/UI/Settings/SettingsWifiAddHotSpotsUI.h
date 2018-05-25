#ifndef SETTINGSWIFIADDHOTSPOTSUI_H
#define SETTINGSWIFIADDHOTSPOTSUI_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "HMIWidgets/CComboBox.h"
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsWifiAddHotSpotsUI : public QWidget ,public CView
{
    Q_OBJECT
public:
    SettingsWifiAddHotSpotsUI(QWidget *parent = 0);
    ~SettingsWifiAddHotSpotsUI();
    virtual void viewAction(int state);
signals:

public slots:
    void OnBack();
    void OnAddBtnClicked();
    void OnCancelBtnClicked();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);

private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;

    QLabel *m_pNetNameLabel;
    QLineEdit *m_pNetNameEdit;
    QLabel *m_pNetNameEditLine;

    QLabel *m_pSecurityTypeLabel;
    QLabel *m_pSecurityTypeEditLine;
    CComboBox *m_pSecurityTypeComboBox;

    QLabel *m_pPasswordLabel;
    QLineEdit *m_pPasswordEdit;
    QLabel *m_pPasswordEditLine;
    QLabel *m_pPasswordError;

    QPushButton *m_pAddBtn;
    QPushButton *m_pCancelBtn;
};

#endif // SETTINGSWIFIADDHOTSPOTSUI_H
