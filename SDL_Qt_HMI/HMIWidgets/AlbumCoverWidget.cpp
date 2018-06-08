#include "AlbumCoverWidget.h"
#include "HMIFrameWork/log_interface.h"

#define ALBUM_WIDTH 188
#define ALBUM_HEIGHT 188

#define LIGHT_WIDTH 262
#define LIGHT_HEIGHT 262

AlbumCoverWidget::AlbumCoverWidget(QWidget *parent)
    :CRotationWidget(parent)
    ,m_albumCover(ALBUM_WIDTH, ALBUM_HEIGHT)
    ,m_Mask(ALBUM_WIDTH, ALBUM_HEIGHT)
    ,m_light(LIGHT_WIDTH, LIGHT_HEIGHT)
{

}

void AlbumCoverWidget::setMask(const QBitmap &mask)
{
    m_Mask = mask;
    this->updateAlbumCover();
}

void AlbumCoverWidget::setLight(const QPixmap &light)
{
    m_light = light;
    this->updateAlbumCover();
}

void AlbumCoverWidget::setAlbumCover(const QPixmap &pixmap)
{
    m_albumCover = pixmap.scaled(ALBUM_WIDTH,ALBUM_HEIGHT);
    this->updateAlbumCover();
}

void AlbumCoverWidget::updateAlbumCover()
{
    QPixmap pixmap(LIGHT_WIDTH,LIGHT_HEIGHT);
    pixmap.fill(QColor(0,0,0,0));

    QPixmap temp = m_albumCover;
    temp.setMask(m_Mask);

    //combine
    QPainter painter(&pixmap);
    painter.drawPixmap((LIGHT_WIDTH-ALBUM_WIDTH)/2,(LIGHT_HEIGHT-ALBUM_HEIGHT)/2,
                       ALBUM_WIDTH,ALBUM_HEIGHT,temp);
    painter.drawPixmap(0,0,LIGHT_WIDTH,LIGHT_HEIGHT,m_light);

    CRotationWidget::setPixmap(pixmap);
}

//void AlbumCoverWidget::setPixmap(const QString &path)
//{
//    this->setPixmap(QPixmap(path));
//}

//void AlbumCoverWidget::setPixmap(const QPixmap &pixmap)
//{
//    QPixmap pixmapWithMask(pixmap);
//    pixmapWithMask.setMask(m_Mask);
//}

//void AlbumCoverWidget::setImage(const QString &imagePath)
//{
////    FUNCPRINT;
//    INFO("[mediaanimation] void AlbumCoverWidget::setImage(const QString &imagePath)");
//    m_sImagePath = imagePath;
//    m_pImage = QPixmap(QPixmap(imagePath).scaled(264,264));
//    m_pImage.setMask(m_Mask);
////    INFO("[mediaanimation] imagePath = %s",imagePath.toStdString().c_str())
//    update();
//}

//void AlbumCoverWidget::start()
//{
////    FUNCPRINT;
//    activeAnimation();
//}

//void AlbumCoverWidget::paintEvent(QPaintEvent *)
//{
////    FUNCPRINT;
////    INFO("[mediaanimation] void AlbumCoverWidget::paintEvent(QPaintEvent *)")
//    QPixmap pixNormal(QPixmap(m_sImagePathlowsr).scaled(264,264));
//    pixNormal.setMask(m_Mask);
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform);
//    painter.drawPixmap(QRectF(-15, 0, 165, 264), pixNormal, QRectF(19, 0.0, 165, 264));
//    QTransform t;
//    t.translate(150, 0);
//    t.rotate(m_ipaint, Qt::YAxis);
//    painter.setTransform(t);
//    painter.drawPixmap(QRectF(-165, 0, 165, 264), m_pImage, QRectF(19, 0.0, 165, 264));
//}

//int AlbumCoverWidget::paint() const
//{
////    FUNCPRINT;
//    return m_ipaint;
//}

//void AlbumCoverWidget::setpaint(int paint)
//{
////    FUNCPRINT;
//    m_ipaint = paint;
//    this->update();
//}

//void AlbumCoverWidget::activeAnimation()
//{
////    FUNCPRINT;
////    INFO("[mediaanimation] void AlbumCoverWidget::activeAnimation()")
//    if (m_pPaint)
//    {
//        m_pPaint->setStartValue(270);
//        m_pPaint->setEasingCurve(QEasingCurve::Linear);
//        m_pPaint->setEndValue(360);
//        m_pPaint->setLoopCount(1);
//        m_pPaint->setDuration(700);
//        m_pPaint->start();
//    }
//}

//void AlbumCoverWidget::activeAnimationFinish()
//{
////    FUNCPRINT;
////    INFO("[mediaanimation] m_sImagePathlowsr = %s",m_sImagePathlowsr.toStdString().c_str())
//    m_sImagePathlowsr = m_sImagePath;
////    INFO("[mediaanimation] m_sImagePathlowsr = %s",m_sImagePathlowsr.toStdString().c_str())
//}
