#include "drop_widget.h"
#include <QBitmap>
#include <QPainter>

DropWidget::DropWidget(QWidget *parent) : QDialog(parent)
	, m_bgColor(44, 45, 49)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->setMouseTracking(true);
	m_mousePressed = false;
}

DropWidget::~DropWidget()
{
}

void DropWidget::setBackground(const QImage &image)
{
	m_bgImage = image;
}

void DropWidget::setBackgroundColor(QColor color)
{
	m_bgColor = color;
}

void DropWidget::setTitle(const QString &title)
{
	m_title = title;
}

void DropWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		m_mousePressed = true;
	}

	m_movePoint = event->globalPos() - pos(); 
}

void DropWidget::mouseReleaseEvent(QMouseEvent *)
{
	m_mousePressed = false;
}

void DropWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(m_mousePressed) {
		QPoint move_pos = event->globalPos();
		move(move_pos - m_movePoint);
	}
}

void DropWidget::paintEvent( QPaintEvent *event)
{
	if (!m_bgImage.isNull()) {
		drawBackground(event);
	} else {
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(m_bgColor);
		painter.drawRect(this->rect());

		int radius = 4;
		QSize maskSize(this->size().width(), this->size().height());
		QBitmap mask(maskSize);
		QPainter maskPainter(&mask);
		maskPainter.setRenderHint(QPainter::Antialiasing);
		maskPainter.setRenderHint(QPainter::SmoothPixmapTransform);
		maskPainter.fillRect(this->rect(), Qt::white);
		maskPainter.setBrush(QColor(0, 0, 0));
		maskPainter.drawRoundedRect(QRect(QPoint(0, 0), maskSize), radius, radius);
		this->setMask(mask);
		QWidget::paintEvent(event);
	}

	if (!m_title.isEmpty()) {
		QFontMetrics fm = this->fontMetrics();
		int textWidth = fm.width(m_title);
		int x = (this->width() - textWidth) / 2;
		int y = 20;
		QPainter painter(this);
		painter.drawText(x, y, m_title);
	}
}

void DropWidget::drawBackground(QPaintEvent *event)
{
	QPainter painter(this);

	QImage image = m_bgImage;
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap::fromImage(image.copy(0, 0, image.width(), 1)));

	// ´°¿ÚtopÔ²½Ç´¦Àí
	int radius = 4;
	QSize maskSize(this->size().width(), this->size().height());
	QBitmap mask(maskSize);
	QPainter maskPainter(&mask);
	maskPainter.setRenderHint(QPainter::Antialiasing);
	maskPainter.setRenderHint(QPainter::SmoothPixmapTransform);
	maskPainter.fillRect(this->rect(), Qt::white);
	maskPainter.setBrush(QColor(0, 0, 0));
	maskPainter.drawRoundedRect(QRect(QPoint(0, 0), maskSize), radius, radius);
	this->setMask(mask);
	QWidget::paintEvent(event);
}
