#ifndef APPBASE_H
#define APPBASE_H

//#include "MainMenu.h"
#include "ui_interface.h"
#include <QWidget>
#include <QLabel>
#include <app_list_interface.h>
#include <QLineEdit>

#define AppControl m_pList->getActiveApp()

#define SCREEN_WIDTH  800//1280
#define SCREEN_HEIGHT  480//800

typedef struct softButton{
    bool b_isHighlighted;
    int i_softButtonID;
    std::string str_text;
    softButton()
    {
        b_isHighlighted = false;
        i_softButtonID = 0;
        str_text.clear();
    }
}SSoftButton;

class AppBase : public QWidget
{
    Q_OBJECT
public:
    explicit AppBase(AppListInterface * pList, QWidget *parent = 0);
    ~AppBase();

    // Bug #9671
    static void SetEdlidedText(QLabel *pLabel,QString strText,int iWidth, Qt::AlignmentFlag alignMode = Qt::AlignLeft);
    static void SetEdlidedText(QLineEdit *pEdit,QString strText,int iWidth);
protected:
    //virtual void setTitle(QString title){((MainMenu*)parent()->parent()->parent())->SetTitle(title);}

signals:
    void onButtonClicked(int btnID);
    void onListClicked(int listID);
    void onSpaceClicked();
    void menuBtnClicked(QString);

protected:
    void setBkgImage(const char *img);
    AppListInterface * m_pList;
};

#endif // APPBASE_H
