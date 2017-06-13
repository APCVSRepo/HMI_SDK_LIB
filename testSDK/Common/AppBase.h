#ifndef APPBASE_H
#define APPBASE_H

//#include "MainMenu.h"
#include "UIInterface.h"
#include <QWidget>
#include <QLabel>
#include <AppListInterface.h>
#include <QLineEdit>

#define AppControl m_pList->getActiveApp()

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

    static void SetEdlidedText(QLabel *pLabel,QString strText,int iWidth);
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
