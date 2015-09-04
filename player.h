#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>

class QMediaPlaylist;
class Player : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    void setPlayList(const QStringList &playList);

    void setIndex(int index);
    int index() const;

private slots:
    void slotError(QMediaPlayer::Error error);

private:
    QMediaPlaylist *m_playList;
};

#endif // PLAYER_H
