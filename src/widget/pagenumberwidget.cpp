#include "pagenumberwidget.h"
#include <QtWidgets>

PageNumberWidget::PageNumberWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentPage(1)
    , m_count(0)
{
    this->setMouseTracking(true);
}

PageNumberWidget::~PageNumberWidget()
{

}

void PageNumberWidget::setCount(int count)
{
    if (m_count != count) {
        m_count = count;
        update();
    }
}

void PageNumberWidget::setCurrentPage(int page)
{
    m_currentPage = page;
}

int PageNumberWidget::currentPage() const
{
    return m_currentPage;
}

void PageNumberWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (inPageNumber(e->pos())) {
        this->setCursor(Qt::PointingHandCursor);
    } else {
        this->setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseMoveEvent(e);
}

void PageNumberWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        int page = inPageNumber(e->pos());
        if (m_currentPage != page) {
            m_currentPage = page;
            emit sigPageChanged(m_currentPage);
            update();
        }
    }
    QWidget::mouseReleaseEvent(e);
}

void PageNumberWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    int radius = this->width();
    int space = 10;
    int xPos = 0;
    int yPos = this->height() - m_count * radius - (m_count - 1) * space;

    m_rects.clear();
    for (int i=0; i<m_count; i++) {
        QRect rect;
        rect.setX(xPos);
        rect.setY(yPos);
        rect.setWidth(radius);
        rect.setHeight(radius);
        m_rects.append(rect);

        if (m_currentPage == i + 1) {
            painter.setBrush(QBrush(QColor(255, 255, 255)));
        } else {
            painter.setBrush(QBrush(QColor(135, 206, 235)));
        }
        painter.drawRoundRect(xPos, yPos, radius, radius, 100, 100);
        yPos += (radius + space);
    }

    QPen pen(QColor(135, 135, 135));
    pen.setWidth(3);
    painter.setPen(pen);
    QFontInfo fm = painter.fontInfo();
    int offset = (radius - fm.pixelSize()) / 2 + 12;
    for (int i=0; i<m_count; i++) {
        painter.drawText(m_rects[i].x() + 6, m_rects[i].y() + offset, QString::number(i+1));
    }
}

int PageNumberWidget::inPageNumber(QPoint pos) const
{
    for (int i=0; i<m_rects.count(); i++) {
        if (m_rects[i].contains(pos)) {
            return i + 1;
        }
    }
    return 0;
}
