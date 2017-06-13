#ifndef CHOICESETVR_H
#define CHOICESETVR_H

#include <QWidget>
#include <QLabel>
#include <string>

class CChoiceSetVR : public QWidget
{
    Q_OBJECT
public:
    explicit CChoiceSetVR(QWidget *parent = 0);
    ~CChoiceSetVR();

    void SetTitle(std::string strTitle);
    void SetChoice(int iPos,std::string strChoice);
protected:
    void mousePressEvent(QMouseEvent * event);
signals:
    void pressed();
public slots:


private:
    QLabel *m_pTitleLab;
    QLabel m_aChoiceLab[6];
    QLabel m_aCmdLab[3];
};

#endif // CHOICESETVR_H
