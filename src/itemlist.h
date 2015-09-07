#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QObject>
#include <QMap>

class ItemList : public QObject
{
    Q_OBJECT
public:
    explicit ItemList(QObject *parent = 0);
    const QMap<int, QString> &data() const;

private:
    void praseFile(const QString &filename);

private:
    QMap<int, QString> m_data;
};

#endif // ITEMLIST_H
