#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QGraphicsOpacityEffect>
class CPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CPushButton(QWidget *parent = 0);
    void SetStyle(const QString& style);

    bool event(QEvent *e);
protected:
    void MouseEvent(QEvent *e);
signals:

public slots:
private:
    QGraphicsOpacityEffect* m_pEffect;

};

#endif // CPUSHBUTTON_H
