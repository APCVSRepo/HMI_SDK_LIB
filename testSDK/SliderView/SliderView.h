#ifndef SLIDERVIEW_H
#define SLIDERVIEW_H

#include <QWidget>
#include <Common/CustomButton.h>
#include "Common/AppBase.h"
#include <QLabel>
#include <QSlider>
#include <QTimer>

class CSliderView : public QWidget
{
    Q_OBJECT
public:
    explicit CSliderView(AppListInterface *pList,QWidget *parent = 0);
    ~CSliderView();
protected:
    virtual void showEvent(QShowEvent * e);
signals:

public slots:
    void OnReturnBtnClicked();
    void OnSoftBtnClicked(int iSoftBtnID);
    void OnSliderValueChanged(int iValue);
    void OnTimeOut();
private:
    void UpdateFooter(int iPos);
    AppListInterface *m_pList;

    QLabel *m_pAppNameLab;
    QLabel *m_pHeaderLab;
    QLabel *m_pFooterLab;
    QSlider *m_pSlider;

    CCustomButton *m_pReturnBtn;
    CCustomButton m_aSoftBtn[2];

    std::vector<std::string> m_FooterStrVec;
    bool m_bDynamic;

    QTimer *m_pTimer;
};

#endif // SLIDERVIEW_H
