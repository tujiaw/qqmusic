#include "response.h"
#include "../tools/json.h"
#include <QDebug>

Response::Response(const QByteArray &data, QObject *parent)
    : QObject(parent)
{
    QVariantMap json = json::toMap(data);
    m_resCode = json["showapi_res_code"].toInt();
    m_resError = json["showapi_res_error"].toString();
    m_resBody = json["showapi_res_body"].toMap();
}

int Response::resCode() const
{
    return m_resCode;
}

QString Response::resError() const
{
    return m_resError;
}

MusicResponse::MusicResponse(const QByteArray &data, QObject *parent)
    : Response(data, parent)
{
    QVariantMap pagebean = m_resBody["pagebean"].toMap();
    m_pageBean.retCode = pagebean["ret_code"].toInt();
    m_pageBean.currentPage = pagebean["currentPage"].toInt();
    m_pageBean.totalPage = pagebean["totalpage"].toInt();
    m_pageBean.title = pagebean["title"].toString();
    m_pageBean.picUrl = pagebean["picUrl"].toString();
    QVariantList list = pagebean["songlist"].toList();
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        QVariantMap item = (*iter).toMap();
        Song song;
        song.albumid = item["albumid"].toDouble();
        song.albumname = item["albumname"].toString();
        song.downUrl = item["downUrl"].toString();
        song.singerid = item["singerid"].toDouble();
        song.singername = item["singername"].toString();
        song.songid = item["songid"].toDouble();
        song.songname = item["songname"].toString();
        song.url = item["url"].toString();

        // fix
        song.url += "?fromtag=0";

        m_pageBean.songList.append(song);
    }
}

const PageBean& MusicResponse::pageBean() const
{
    return m_pageBean;
}

const QList<Song>& MusicResponse::songList() const
{
    return m_pageBean.songList;
}
