#ifndef ALBUMCOVERWIDGET_H
#define ALBUMCOVERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QBitmap>
#include "CRotationWidget.h"

class AlbumCoverWidget : public CRotationWidget
{
    Q_OBJECT

public:
    explicit AlbumCoverWidget(QWidget *parent = 0);

    void setMask(const QBitmap &mask);  //262x262
    void setLight(const QPixmap &light);//262x262

    void setAlbumCover(const QPixmap &pixmap);  //188x188
//    void setPixmap(const QString &path);
//    void setPixmap(const QPixmap &pixmap);

//    void setImage(const QString &imagePath);
//    void start();

//private:
//    void paintEvent(QPaintEvent *);
//    int paint() const;
//    void setpaint(int paint);
//    void activeAnimation();

signals:

public slots:
//    void activeAnimationFinish();

private:
    void updateAlbumCover();
//    int m_ipaint;
//    QPixmap m_pImage;
//    QString  m_sImagePath;
//    QString  m_sImagePathlowsr;

    QPixmap m_albumCover;
    QBitmap m_Mask;
    QPixmap m_light;
public:
//    QPropertyAnimation*    m_pPaint;
};

#endif // ALBUMCOVERWIDGET_H
