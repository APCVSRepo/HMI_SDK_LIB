#include "CustomComboboxItem.h"
#include <QUrl>
#include "../Common/CustomButton.h"

CustomComboboxItem::CustomComboboxItem(int w,int h,QWidget *parent) : QLabel(parent),
    m_iBkState(NORMAL_STATE)
{
    //setFixedSize(w,h);
    //m_pBackgroudLab = new QLabel(this);
    //m_pBackgroudLab->setGeometry(0,0,w,h);
    setFixedSize(w,h);
    setAutoFillBackground(true);

    m_pMainLayout = new QHBoxLayout(this);
    m_pIconLab = new QLabel;
    m_pTextLab = new QLabel;
    m_pMenuArrowLab = new QLabel;
    m_pMainLayout->setMargin(0);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addWidget(m_pIconLab,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pTextLab,0,Qt::AlignLeft);
    m_pMainLayout->addStretch(1);
    m_pMainLayout->addWidget(m_pMenuArrowLab,0,Qt::AlignRight);

    m_pTextLab->setStyleSheet("font: 32px \"Liberation Serif\";color:rgb(0,0,0);border: 0px");


    QPixmap pixmap(":/images/rightarrow.png");
    QPixmap fitpixmap=pixmap.scaled(30,30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_pMenuArrowLab->setPixmap(fitpixmap);
}

CustomComboboxItem::~CustomComboboxItem()
{
    //delete m_pBackgroudLab;
    delete m_pMainLayout;
    delete m_pIconLab;
    delete m_pTextLab;
    delete m_pMenuArrowLab;
}

void CustomComboboxItem::setText(QString text)
{
    QFontMetrics qfm(m_pTextLab->font());
    m_pTextLab->setText(qfm.elidedText(text,Qt::ElideRight,width() - height()));
}

void CustomComboboxItem::setIsMenu(bool isMenu)
{
    if (isMenu)
        m_pMenuArrowLab->setHidden(false);
    else
        m_pMenuArrowLab->setHidden(true);
}

void CustomComboboxItem::SetBkPic(QString strNormalPicPath,
                                  QString strPressPicPath,
                                  QString strHoverPicPath)
{
    m_strNormalBk = strNormalPicPath;
    m_strHoverBk = strHoverPicPath;
    m_strPressBk = strPressPicPath;

    QPixmap pixmap(m_strNormalBk);
    pixmap = pixmap.scaled(width(),height(),
                           Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    setPixmap(pixmap);
    m_iBkState = NORMAL_STATE;
}

void CustomComboboxItem::ChangeBkPic(int iFlag)
{    
    QPixmap *pPixmap = NULL;
    if (iFlag != m_iBkState) {
        if (iFlag == NORMAL_STATE) {
            pPixmap = new QPixmap(m_strNormalBk);
        } else if (iFlag == HOVER_STATE) {
            pPixmap = new QPixmap(m_strHoverBk);
        } else {
            pPixmap = new QPixmap(m_strPressBk);
        }
        *pPixmap = pPixmap->scaled(width(),height(),
                                   Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation);
        setPixmap(*pPixmap);
        m_iBkState = iFlag;
        delete pPixmap;
    }
}

QString CustomComboboxItem::GetItemText()
{
    return m_pTextLab->text();
}

void CustomComboboxItem::mousePressEvent(QMouseEvent *event)
{
    ChangeBkPic(PRESS_STATE);
}

void CustomComboboxItem::mouseReleaseEvent(QMouseEvent *event)
{
    ChangeBkPic(NORMAL_STATE);
    emit ItemClicked(this);
    emit ItemClicked(m_iIndex);
}

void CustomComboboxItem::SetIndex(int iIndex)
{
    m_iIndex = iIndex;
}

void CustomComboboxItem::SetLeftIcon(std::string strIcon)
{
    if (strIcon.empty()) {
        m_pIconLab->setMinimumWidth(0);
        m_pIconLab->setStyleSheet("max-width:0px;max-height:0px");
    } else {
        m_pIconLab->setMinimumWidth(height());
#if defined(WINCE)
        QString strTemp = QString("background:transparent;border:transparent;padding:%1px;image:url(%2)").arg(height()*0.15).arg(ChangeSlash(QUrl(strIcon.c_str()).path().toLocal8Bit().data()).c_str());
#else
        QString strTemp = QString("background:transparent;border:transparent;padding:%1px;image:url(%2)").arg(height()*0.15).arg(ChangeSlash(QUrl(strIcon.c_str()).path().toStdString()).c_str());
#endif
        m_pIconLab->setStyleSheet(strTemp);
    }
}


