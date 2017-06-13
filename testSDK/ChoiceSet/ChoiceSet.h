#ifndef CHOICESET_H
#define CHOICESET_H

#include <QWidget>
#include "AppListInterface.h"
#include "Common/CustomButton.h"
#include "Common/CustomListView.h"
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include "ChoiceSetVR.h"

class CChoiceSet : public QWidget
{
    Q_OBJECT
public:
    explicit CChoiceSet(AppListInterface *pList,QWidget *parent = 0);
    ~CChoiceSet();
protected:
    void showEvent(QShowEvent * e);
signals:

public slots:
    void OnChoiceVRPressed();
    void OnReturnBtnClicked();
    void OnTimeOut();
    void OnListItemClicked(int iChoiceId);
    void OnEditChanged(QString strkey);
private:
    enum INTERACTIONMODE {BOTH = 0,VR_ONLY,MANUAL_ONLY};
    int m_iInteractionMode;

    CCustomButton *m_pReturnBtn;    
    QWidget *m_pTopText;
    QLabel *m_pInitText;
    QLineEdit *m_pInitEdit;
    CustomListView *m_pListView;
    QVBoxLayout *m_pMainLayout;
    QHBoxLayout *m_pTopLayout;
    CChoiceSetVR *m_pChoiceVR;

    QTimer *m_pTimer;

    AppListInterface *m_pList;
};

#endif // CHOICESET_H
