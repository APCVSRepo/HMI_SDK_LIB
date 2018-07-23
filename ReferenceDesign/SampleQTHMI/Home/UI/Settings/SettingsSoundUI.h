#ifndef SETTINGSSOUNDUI_H
#define SETTINGSSOUNDUI_H
#include <QWidget>
#include "HMIWidgets/SliderSelect.h"
#include "HMIWidgets/CPushButton.h"
#include "QLabel"
#include "HMIWidgets/SliderSelect.h"
#include "HMIWidgets/CVListWidget.h"
#include <QList>
#include "HMIFrameWork/CView.h"

class SettingsSoundUI:public QWidget , public CView
{
    Q_OBJECT
public:
    SettingsSoundUI(QWidget *parent = NULL);
    ~SettingsSoundUI();
    virtual void viewAction(int state);

    void InitTrebleVoice();
    void InitAltoVoice();
    void InitBassVoice();
    void InitList();
    void InitConnect();
public slots:
    void OnTerbleLeft();
    void OnTerbleRight();
    void OnAltoLeft();
    void OnAltoRight();
    void OnBassLeft();
    void OnBassRight();
    void OnBack();
    void OnReset();

    void OnListBtnRelease(int index,int btnIndex);
private:
    void TrebleHandler(int step);
    void AltoHandler(int step);
    void BassHandler(int step);
    int GetTerbleVoice();
    int GetAltoVoice();
    int GetBassVoice();
private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;

    CPushButton *m_pResetBtn;
    QLabel *m_pTrebleLabel;
    QLabel *m_pTrebleDataLabel;
    CPushButton *m_pTrebleLeftBtn;
    CPushButton *m_pTrebleRightBtn;

    QLabel *m_pAltoLabel;
    QLabel *m_pAltoDataLabel;
    CPushButton *m_pAltoLeftBtn;
    CPushButton *m_pAltoRightBtn;

    QLabel *m_pBassLabel;
    QLabel *m_pBassDataLabel;
    CPushButton *m_pBassLeftBtn;
    CPushButton *m_pBassRightBtn;

    QList<SliderSelect*> m_trebleList;
    QList<SliderSelect*> m_altoList;
    QList<SliderSelect*> m_bassList;
    int m_iTrebleValue;
    int m_iAlto;
    int m_iBass;

    CVListWidget *m_pVlist;


};

#endif // SETTINGSSOUNDUI_H
