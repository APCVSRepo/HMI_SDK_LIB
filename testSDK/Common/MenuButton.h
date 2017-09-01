#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <QPushButton>
#include <string>

class MenuButton : public QPushButton
{
public:
    MenuButton(QWidget *pParent=NULL);
    ~MenuButton();
    virtual void setText(const QString &text);
    virtual void setIcon(const QString on,const QString off);
    virtual void setIcon(QImage on,QImage off);
    virtual void setActive(bool active);
    std::string Text();
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    QImage m_pOnImage;
    QImage m_pOffImage;
    bool   m_isActive;
    QString m_text;
};

#endif // MENUBUTTON_H
