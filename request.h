#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);

    virtual QString getUrl() = 0;
    static QString getTimestamp();
    static QString getMd5(const QList<QPair<QString, QString>> &argv, const QString &secret);

protected:
    QString m_address;
    int m_appId;
    QString m_secret;
    QString m_sign;
    QString m_timestamp;
    QString m_signMethod;
};

class MusicRequest : public Request
{
    Q_OBJECT
public:
    MusicRequest(int appId, const QString &secret, QObject *parent = 0);
    QString getUrl();

    void setItemId(int itemId);
    void setPage(int page);

private:
    int m_itemId;
    int m_page;
};

#endif // REQUEST_H
