#ifndef SETTINGSSPEECHRECOGNITIONUI_H
#define SETTINGSSPEECHRECOGNITIONUI_H

#include <QWidget>
#include "HMIWidgets/CVListWidget.h"
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsSpeechRecognitionUI : public QWidget,public CView
{
    Q_OBJECT

public:
    explicit SettingsSpeechRecognitionUI(QWidget *parent = 0);
    ~SettingsSpeechRecognitionUI();
    virtual void viewAction(int state);

    void InitConnect();
public slots:
    void OnBack();
    void OnListBtnClick(int,int);
    void OnListClick(int);
private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;
    CVListWidget* m_pVlist;
    QLabel *m_pBackgroundLabel;
};

#endif // SETTINGSSPEECHRECOGNITIONUI_H
