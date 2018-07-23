#ifndef BOOTANIMATIONUI_H
#define BOOTANIMATIONUI_H

#include <QWidget>
#include "HMIFrameWork/CView.h"
#include "BootAnimation.h"
class BootAnimationUI : public QWidget ,public CView
{
    Q_OBJECT
public:
    explicit BootAnimationUI(QWidget *parent = 0);
    virtual void viewAction(int state);
signals:

public slots:
    void OnPlayFinish();

private:
    BootAnimation *m_pAnimation;
};

#endif // BOOTANIMATIONUI_H
