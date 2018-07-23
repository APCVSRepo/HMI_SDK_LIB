#ifndef SLIDERVIEW_H
#define SLIDERVIEW_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QTimer>
#include <QPushButton>
#include "SDLApps/Templates/Common/AppBase.h"
#include "HMIWidgets/TopNavigateWidget.h"

class CSliderView : public QWidget {
    Q_OBJECT
public:
    explicit CSliderView(AppListInterface *pList, QWidget *parent = 0);
    ~CSliderView();
protected:
    virtual void showEvent(QShowEvent *e);
signals:

public slots:
    void OnSliderValueChanged(int iValue);
    void OnTimeOut();

    void OnSaveBtnClicked();
    void OnReturnBtnClicked();

private:
    void UpdateFooter(int iPos);

private:
    AppListInterface *m_pList;
    bool m_bDynamic;
    std::vector<std::string> m_FooterStrVec;
    QLabel *m_pHeaderLab;
    QLabel *m_pFooterLab;
    QSlider *m_pSlider;

    //navigate item
    TopNavigateWidget *m_pTopWidget;

    QPushButton *m_pSaveBtn;
    QPushButton *m_pReturnBtn;

    QTimer *m_pTimer;
};

#endif // SLIDERVIEW_H
