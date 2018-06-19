#ifndef CHOICESET_H
#define CHOICESET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include "app_list_interface.h"
#include "SDLApps/Templates/Common/CustomListView.h"
#include "ChoiceSetVR.h"
#include "HMIWidgets/CPushButton.h"

class CChoiceSet : public QWidget {
    Q_OBJECT

public:
    explicit CChoiceSet(AppListInterface *pList, QWidget *parent = 0);
    ~CChoiceSet();

protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *);

signals:

public slots:
    void OnChoiceVRClicked();
    void OnReturnBtnClicked();
    void OnTimeOut();
    void OnListItemClicked(int iChoiceId);
    void OnEditChanged(QString strkey);

private:
    void SetEditable(bool editable);

private:
    enum INTERACTIONMODE {BOTH = 0, VR_ONLY, MANUAL_ONLY};
    int m_iInteractionMode;

    AppListInterface *m_pList;

    QLineEdit *m_pInitEdit;
    CustomListView *m_pListView;

    CChoiceSetVR *m_pChoiceVR;
    QTimer *m_pTimer;

    QLabel *m_pBackground;
    CPushButton *m_pReturnBtn;
    QLabel *m_pBackIcon;
};

#endif // CHOICESET_H
