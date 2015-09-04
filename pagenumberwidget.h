#ifndef PAGENUMBERWIDGET_H
#define PAGENUMBERWIDGET_H

#include <QWidget>

class QHBoxLayout;
class PageNumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageNumberWidget(QWidget *parent = 0);
    ~PageNumberWidget();

    void setCount(int count);

signals:
    void sigPageChanged(int pageNumber);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);

private:
    int inPageNumber(QPoint pos) const;

private:
    int m_count;
    int m_currentPage;
    QList<QRect> m_rects;
};

#endif // PAGENUMBERWIDGET_H
