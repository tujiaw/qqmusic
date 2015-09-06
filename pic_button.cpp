#include "pic_button.h"
#include <QMouseEvent>
#include <QPainter>
#include <QStaticText>

PicButton::PicButton(QWidget *parent)
	: QPushButton(parent), status_(NORMAL), controlStatus_(STATUS_NONE), number_(0)
{
}

PicButton::~PicButton()
{
}


void PicButton::setPicName(const QString &normal, const QString &hover, const QString &pressed, const QString &disable)
{
	pixmaps_[NORMAL].load(normal);
	pixmaps_[ENTER].load(hover);
	pixmaps_[PRESS].load(pressed);
	pixmaps_[RELEASE].load(disable);
	if (numberPixmap_.isNull()) {
		this->setFixedSize(pixmaps_[NORMAL].size());
	}
}

void PicButton::setImages(const QPixmap &normal, const QPixmap &hover, const QPixmap &pressed, const QPixmap &disable)
{
	pixmaps_[NORMAL] = normal;
	pixmaps_[ENTER] = hover;
	pixmaps_[PRESS] = pressed;
	pixmaps_[RELEASE] = disable;
	if (numberPixmap_.isNull()) {
		this->setFixedSize(pixmaps_[NORMAL].size());
	}
}

void PicButton::setControlStatus(Status status)
{
	controlStatus_ = status;
	update();
}

void PicButton::setNumber(int number)
{
	number_ = number;
	update();
}

int PicButton::getNumber() const
{
	return number_;
}

void PicButton::setNumberPicName(const QString &imagePath)
{
	numberPixmap_.load(imagePath);
	this->setFixedWidth(this->width() + numberPixmap_.width() / 2);
	update();
}

void PicButton::enterEvent(QEvent *)
{
	status_ = ENTER;
	update();
}

void PicButton::leaveEvent(QEvent *)
{
	status_ = NORMAL;
	update();
}

void PicButton::mousePressEvent(QMouseEvent *event)
{
	QPushButton::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		status_ = PRESS;
	}
}

void PicButton::mouseReleaseEvent(QMouseEvent *event)
{
	QPushButton::mouseReleaseEvent(event);
	if (status_ == PRESS && event->button() == Qt::LeftButton) {
		status_ = RELEASE;
	}
}

void PicButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	int index = NORMAL;
	if (STATUS_NONE == controlStatus_) {

		if (this->isEnabled()) {
			index = (status_== RELEASE ? NORMAL : status_);
		} else {
			index = RELEASE;
		}
	} else {
		index = controlStatus_;
	}

	painter.drawPixmap(pixmaps_[index].rect(), pixmaps_[index]);
	if (!numberPixmap_.isNull() && number_ > 0) {
		int x = this->width() - numberPixmap_.width();
		int y = this->height() - numberPixmap_.height();
		painter.drawPixmap(x, y, numberPixmap_.width(), numberPixmap_.height(), numberPixmap_);
	}
}

