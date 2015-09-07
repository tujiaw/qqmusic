#include "player.h"
#include <QMediaPlaylist>

Player::Player(QObject *parent) : QMediaPlayer(parent)
{
    m_playList = new QMediaPlaylist;
    m_playList->setCurrentIndex(1);

    this->setPlaylist(m_playList);
    this->setVolume(100);

    connect(this, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(slotError(QMediaPlayer::Error)));
}

void Player::setPlayList(const QStringList &playList)
{
    m_playList->clear();
    for (auto iter = playList.begin(); iter != playList.end(); ++iter) {
        m_playList->addMedia(QUrl(*iter));
    }
}

void Player::setIndex(int index)
{
    m_playList->setCurrentIndex(index);
}

int Player::index() const
{
    return m_playList->currentIndex();
}

void Player::slotError(QMediaPlayer::Error error)
{
    switch (error) {
    case QMediaPlayer::NoError:
        qDebug() << "NoError";
        break;
    case QMediaPlayer::ResourceError:
        qDebug() << "ResourceError";
        break;
    case QMediaPlayer::FormatError:
        qDebug() << "FormatError";
        break;
    case QMediaPlayer::NetworkError:
        qDebug() << "NetworkError";
        break;
    case QMediaPlayer::AccessDeniedError:
        qDebug() << "AccessDeniedError";
        break;
    case QMediaPlayer::ServiceMissingError:
        qDebug() << "ServiceMissingError";
        break;
    case QMediaPlayer::MediaIsPlaylist:
        qDebug() << "MediaIsPlaylist";
        break;
    default:
        qDebug() << "others";
        break;
    }
}
