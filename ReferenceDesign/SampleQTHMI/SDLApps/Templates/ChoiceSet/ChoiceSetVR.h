#ifndef CHOICESETVR_H
#define CHOICESETVR_H

#include <string>
#include <QWidget>
#include <QLabel>
#include "HMIWidgets/CRotationWidget.h"
#include "HMIWidgets/CPushButton.h"

class CChoiceSetVR : public QWidget {
    Q_OBJECT
public:
    explicit CChoiceSetVR(QWidget *parent = 0);
    ~CChoiceSetVR();

    void SetTitle(std::string strTitle);
    void SetChoice(int iPos, std::string strChoice);

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void pressed();
    void released();

public slots:
    void OnVRBtnClicked();

private:
    QLabel *m_pTitleLab;

    QLabel *m_pTopLine;
    QLabel *m_pBottomLine;

    QWidget *m_pChoiceArea;
    QLabel m_aChoiceLab[6];

    CRotationWidget *m_pRotate;
    CPushButton *m_pVRBtn;
};

#endif // CHOICESETVR_H
