#include "itemlist.h"
#include <QFile>
#include <QDebug>
#include <iostream>

ItemList::ItemList(QObject *parent) : QObject(parent)
{
    praseFile(":/itemlist");
}

const QMap<int, QString> &ItemList::data() const
{
    return m_data;
}

void ItemList::praseFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    while (!file.atEnd()) {
        QString line = QString::fromUtf8(file.readLine());
        QStringList strList = line.split("|");
        if (strList.size() >= 2) {
            QStringList itemId = strList.at(0).split("=");
            QString name = strList.at(1).trimmed();
            if (itemId.size() >= 2 && !name.isEmpty()) {
                int id = itemId.at(1).toInt();
                if (id) {
                    m_data[id] = name;
                }
            }
        }
    }

    file.close();
}
