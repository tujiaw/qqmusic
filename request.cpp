#include "request.h"
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>

Request::Request(QObject *parent)
    : QObject(parent)
{
}

QString Request::getTimestamp()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyyMMddHHmmss");
}

QString Request::getMd5(const QList<QPair<QString, QString>> &argv, const QString &secret)
{
   QList<QPair<QString, QString>> list = argv;
   qSort(list.begin(), list.end(), [](const QPair<QString, QString> &left, const QPair<QString, QString> &right) {
        return left.first < right.first;
   });
   QString str;
   for (auto iter = list.begin(); iter != list.end(); ++iter) {
       str += ((*iter).first + (*iter).second);
   }
   str += secret.toLower();
   return QCryptographicHash::hash(str.toLocal8Bit(), QCryptographicHash::Md5).toHex();
}


MusicRequest::MusicRequest(int appId, const QString &secret, QObject *parent)
    : Request(parent)
    , m_itemId(5)
    , m_page(1)
{
    m_address = "http://route.showapi.com/213-3";
    m_signMethod = "md5";
    m_appId = appId;
    m_secret = secret;
}

QString MusicRequest::getUrl()
{
    QList<QPair<QString, QString>> argv;
    argv << QPair<QString, QString>("showapi_appid", QString::number(m_appId));
    argv << QPair<QString, QString>("showapi_timestamp", getTimestamp());
    argv << QPair<QString, QString>("itemid", QString::number(m_itemId));
    argv << QPair<QString, QString>("page", QString::number(m_page));
    m_sign = getMd5(argv, m_secret);

    QString result = m_address + "?showapi_sign=" + m_sign;
    for (auto iter = argv.begin(); iter != argv.end(); ++iter) {
        result += ("&" + (*iter).first + "=" + (*iter).second);
    }

    //qDebug() << result;
    return result;
}

void MusicRequest::setItemId(int itemId)
{
    m_itemId = itemId;
}

void MusicRequest::setPage(int page)
{
    m_page = page;
}
