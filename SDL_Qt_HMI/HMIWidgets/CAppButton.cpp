#include "CAppButton.h"
#include <QPainter>
#include <QRgb>
#include <QUrl>
#include "global_first.h"

CAppButton::CAppButton(QWidget *pParent): MenuButton(pParent) {
    m_pEffect = new QGraphicsOpacityEffect();
    m_pEffect->setOpacity(1);
    this->setGraphicsEffect(m_pEffect);

    m_FuncId = -1;
    m_pressx = m_pressy = 0;
    m_bPressDown = false;

    MenuButton::setActive(true);
}

CAppButton::~CAppButton() {

}

void CAppButton::setIcon(const QString on, const QString off, bool bPaint, bool bCustomize) {
    QImage img_on, img_off;
    if (bPaint) {
        if(bCustomize)
        {
            {
                img_on.load(":/SDLApps/Source/images/app_bg.png");

                QImage onImage(on);
                onImage = onImage.scaled(46, 46, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

                QPainter painter(&img_on);
                painter.drawImage(37, 37, onImage, 0, 0);
            }

            {
                img_off.load(":/SDLApps/Source/images/app_bg.png");

                QImage offImage(off);
                offImage = offImage.scaled(46, 46, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

                QPainter painter(&img_off);
                painter.drawImage(37, 37, offImage);
            }
        }
        else
        {
            {
                img_on.load(":images/app_on.png");
                QImage onImage(on);
                onImage = onImage.scaled(width() * 11 / 30, width() * 0.6, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                do {
                    QPainter painter(&img_on);
                    QRect irect = onImage.rect();
                    QRect orect = img_on.rect();
                    int sx = (orect.width() - irect.width()) / 2;
                    int sy = (orect.height() - irect.height()) / 4;
                    painter.drawImage(sx, sy, onImage, 0, 0);
                } while (0);
            }

            {
                img_off.load(":images/app_off.png");
                QImage offImage(off);
                offImage = offImage.scaled(width() * 0.6, height() * 0.6, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                do {
                    QPainter painter(&img_off);
                    QRect irect = offImage.rect();
                    QRect orect = img_off.rect();
                    int sx = (orect.width() - irect.width()) / 2;
                    int sy = (orect.height() - irect.height()) / 4;
                    painter.drawImage(sx, sy, offImage);
                } while (0);
            }
        }
    } else {
        img_on.load(on);
        img_off.load(off);
    }

    MenuButton::setIcon(img_on, img_off);
}

void CAppButton::setFuncId(int id) {
    m_FuncId = id;
}

void CAppButton::setStringId(std::string strId) {
    m_strId = strId;
}

std::string CAppButton::getStrId() {
    return m_strId;
}

int CAppButton::getFuncId() {
    return m_FuncId;
}

void CAppButton::mousePressEvent(QMouseEvent *e) {

    m_pEffect->setOpacity(0.4);
    this->setGraphicsEffect(m_pEffect);

    m_pressx = e->x();
    m_pressy = e->y();
    m_bPressDown = true;
    e->ignore();
}

void CAppButton::mouseReleaseEvent(QMouseEvent *e) {

    m_pEffect->setOpacity(1);
    this->setGraphicsEffect(m_pEffect);

    if (m_bPressDown && (abs(e->x() - m_pressx) < 20 && abs(e->y() - m_pressy) < 20)) {
        emit OnClicked(m_strId);
        emit clickedWitchFuncId(m_FuncId);
        m_bPressDown = false;
        m_pressx = m_pressy = 0;
    } else {
        e->ignore();
    }
}
