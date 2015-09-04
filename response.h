#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QVariantMap>

class Response : public QObject
{
    Q_OBJECT
public:
    explicit Response(const QByteArray &data, QObject *parent = 0);

    int resCode() const;
    QString resError() const;

protected:
    int m_resCode;
    QString m_resError;
    QVariantMap m_resBody;
};

typedef struct {
    double albumid;
    QString albumname;
    QString downUrl;
    double singerid;
    QString singername;
    double songid;
    QString songname;
    QString url;
} Song;

typedef struct {
    int retCode;
    int currentPage;
    int totalPage;
    QString title;
    QString picUrl;
    QList<Song> songList;
} PageBean;

class MusicResponse : public Response
{
    Q_OBJECT
public:
    MusicResponse(const QByteArray &data, QObject *parent = 0);

    const PageBean& pageBean() const;
    const QList<Song>& songList() const;

private:
    PageBean m_pageBean;
};

#endif // RESPONSE_H
