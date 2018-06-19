#include "TopNavigateWidget.h"
#include "HMIFrameWork/log_interface.h"

TopNavigateWidget::TopNavigateWidget(QWidget *parent)
    :QWidget(parent)
    ,m_pBack(NULL)
    ,m_pBackIcon(NULL)
    ,m_pBackTitle(NULL)
    ,m_pTitle(NULL)
    ,m_pMenu(NULL)
{
    this->setGeometry(0,0,800,70);

    QFont font;
    //back
    m_pBack = new CPushButton(this);
    m_pBack->setGeometry(0,0,23+15+15+160,70);
    m_pBack->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pBack->setFocusPolicy(Qt::NoFocus);
    m_pBack->hide();

    m_pBackIcon = new QLabel(m_pBack);
    m_pBackIcon->setPixmap(QPixmap(QString(":/SDLApps/Source/images/back.png")));
    m_pBackIcon->setGeometry(23,62-40,15,27);

    m_pBackTitle = new QLabel(m_pBack);
    m_pBackTitle->setGeometry(23+15+15,59-40,160,33);
    m_pBackTitle->setStyleSheet("QLabel{color:#bbffffff;}");
    font.setPixelSize(22);
    m_pBackTitle->setFont(font);

    //title
    m_pTitle = new QLabel(this);
    m_pTitle->setGeometry(23+15+15+160+10,59-40,354,33);
    m_pTitle->setStyleSheet("QLabel{color:rgb(75,169,255);}");
    m_pTitle->setAlignment(Qt::AlignCenter);
    font.setPixelSize(24);
    m_pTitle->setFont(font);
    m_pTitle->hide();

    //menu
    m_pMenu = new CPushButton(this);
    m_pMenu->setGeometry(800-24-46,11,46,46);
    m_pMenu->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/menu.png);background:transparent;}");
    m_pMenu->setFocusPolicy(Qt::NoFocus);
    m_pMenu->hide();

    //signal
    connect(m_pBack,SIGNAL(clicked()),this,SIGNAL(SigBackClicked()));
    connect(m_pMenu,SIGNAL(clicked()),this,SIGNAL(SigMenuClicked()));
}

void TopNavigateWidget::SetTitle(const QString &title)
{
    QFontMetrics qfm(m_pTitle->font());
    QString str = qfm.elidedText(title, Qt::ElideRight, m_pTitle->width());
    m_pTitle->setText(str);
}

void TopNavigateWidget::SetReturnTitle(const QString &title)
{
    QFontMetrics qfm(m_pBackTitle->font());
    QString str = qfm.elidedText(title, Qt::ElideRight, m_pBackTitle->width());
    m_pBackTitle->setText(str);
}

void TopNavigateWidget::ShowBack()
{
    m_pBack->show();
}

void TopNavigateWidget::HideBack()
{
    m_pBack->hide();
}

void TopNavigateWidget::ShowTitle()
{
    m_pTitle->show();
}

void TopNavigateWidget::HideTitle()
{
    m_pTitle->hide();
}

void TopNavigateWidget::ShowMenu()
{
    m_pMenu->show();
}

void TopNavigateWidget::HideMenu()
{
    m_pMenu->hide();
}
