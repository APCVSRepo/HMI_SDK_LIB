#ifndef CAPPBUTTON_H
#define CAPPBUTTON_H

#include <QWidget>
#include "Common/MenuButton.h"

class CAppButton : public MenuButton
{
    Q_OBJECT
public:
    CAppButton(QWidget *pParent=NULL);
    ~CAppButton();
    virtual void setIcon(const QString on,const QString off,bool bPaint = false);
    void setFuncId(int id);
    void setStringId(std::string strId);
    int  getFuncId();
    std::string getStrId();
signals:
    void clickedWitchFuncId(int funcId);
    void OnClicked(std::string strId);
public slots:

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    int    m_FuncId;
    std::string m_strId;
};

#endif // CAPPBUTTON_H
