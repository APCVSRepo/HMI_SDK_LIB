#ifndef TOPNAVIGATEWIDGET_H
#define TOPNAVIGATEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include "HMIWidgets/CPushButton.h"

class TopNavigateWidget: public QWidget
{
    Q_OBJECT

public:
    explicit TopNavigateWidget(QWidget *parent = 0);

    void SetTitle(const QString &title);
    void SetReturnTitle(const QString &title);

    //visible
    void ShowBack();
    void HideBack();
    void ShowTitle();
    void HideTitle();
    void ShowMenu();
    void HideMenu();

signals:
    void SigBackClicked();
    void SigMenuClicked();

public slots:

private:
    CPushButton *m_pBack;
    QLabel *m_pBackIcon;
    QLabel *m_pBackTitle;

    QLabel *m_pTitle;

    CPushButton *m_pMenu;
};

#endif // TOPNAVIGATEWIDGET_H
