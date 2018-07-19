#ifndef VRINTERACTIONVIEW_H
#define VRINTERACTIONVIEW_H

#include <QWidget>
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CRotationWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CVListWidget.h"

class VRInteractionView : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit VRInteractionView(QWidget *parent = 0);
    ~VRInteractionView();

    //CView interface
    virtual void viewAction(int state);

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

signals:

public slots:
    void OnVRBtnClicked();

private:
    CRotationWidget *m_pRotate;
    CPushButton *m_pVRBtn;
    CVListWidget* m_pVlist;
};

#endif // VRINTERACTIONVIEW_H
