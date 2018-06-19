#ifndef VRVIEW_H
#define VRVIEW_H

#include <QWidget>
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CRotationWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CVListWidget.h"

class VRView : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit VRView(QWidget *parent = 0);
    ~VRView();

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
    QLabel *m_pTitleLab;

    QLabel *m_pTopLine;
    QLabel *m_pBottomLine;

    CRotationWidget *m_pRotate;
    CPushButton *m_pVRBtn;

    CVListWidget* m_pVlist;
};

#endif // VRVIEW_H
