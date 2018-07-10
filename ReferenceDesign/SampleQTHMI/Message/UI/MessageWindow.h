#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QWidget>

class MessageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWindow(QWidget *parent = 0);
    ~MessageWindow();

signals:

public slots:

};

#endif // MESSAGEWINDOW_H
