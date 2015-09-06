#ifndef DROP_WIDGET_H
#define DROP_WIDGET_H

#include <QDialog>
#include <QMouseEvent>
#include <qmath.h>

class DropWidget : public QDialog
{
	Q_OBJECT
public:
	explicit DropWidget(QWidget *parent = 0);
	~DropWidget();

	void setBackground(const QImage &image);
	void setBackgroundColor(QColor color);
	void setTitle(const QString &title);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent( QPaintEvent * event);

private:
	void drawBackground(QPaintEvent *event);

private:
	QPoint m_movePoint; //�ƶ��ľ���
	bool m_mousePressed; //����������
	QImage m_bgImage;
	QColor m_bgColor;
	QString m_title;
};

#endif // DROP_WIDGET_H
