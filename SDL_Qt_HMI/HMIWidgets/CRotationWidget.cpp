#include "CRotationWidget.h"
#include "HMIFrameWork/log_interface.h"

CRotationWidget::CRotationWidget(QWidget *parent)
    :QLabel(parent)
    ,m_image()
    ,m_timer(NULL)
    ,m_bRotationStarted(false)
    ,m_nRotationAngle(0)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onRatateTimeout()), Qt::UniqueConnection);

    this->hide();
}

CRotationWidget::~CRotationWidget()
{
    if (!m_timer)
        delete m_timer;
}

void CRotationWidget::setPixmap(const QString &path)
{
    m_image = QPixmap(path);
}

void CRotationWidget::start()
{
    INFO("CRotationWidget::start");
    if (!m_timer->isActive())
    {
        m_bRotationStarted = true;
        show();
        m_timer->start(100);
        onRatateTimeout();
    }
}

void CRotationWidget::stop()
{
    INFO("CRotationWidget::stop()");
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
    hide();
    m_bRotationStarted = false;
    m_nRotationAngle = 0;
}

void CRotationWidget::paintEvent(QPaintEvent *event)
{
    if (m_bRotationStarted && !m_image.isNull())
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        int x = m_image.width()/2;
        int y = m_image.height()/2;

        painter.translate(x, y);
        painter.rotate(m_nRotationDegree);
        painter.translate(-x, -y);

        painter.drawPixmap(0, 0, m_image.width(), m_image.height(), m_image);
    }
    else
    {
        QLabel::paintEvent(event);;
    }
}

void CRotationWidget::onRatateTimeout()
{
    ++ m_nRotationAngle;
    m_nRotationAngle = m_nRotationAngle % 36;
    m_nRotationDegree = 10 * m_nRotationAngle;
    update();
}
