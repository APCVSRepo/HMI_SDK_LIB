#ifndef CAPPBUTTON_H
#define CAPPBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include "SDLApps/Templates/Common/MenuButton.h"

#define ICON_PAGE 8

class CAppButton : public MenuButton {
    Q_OBJECT
public:
    CAppButton(QWidget *pParent = NULL);
    ~CAppButton();
    virtual void setIcon(const QString on, const QString off, bool bPaint = false, bool bCustomize = false);
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
    int m_pressx;
    int m_pressy;
    bool m_bPressDown;
    QGraphicsOpacityEffect* m_pEffect;
};

#endif // CAPPBUTTON_H
