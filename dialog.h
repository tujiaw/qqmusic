#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "drop_widget.h"

namespace Ui {
class Dialog;
}

class MusicRequest;
class ItemList;
class QListWidgetItem;
class Player;
class NetManager;
class Dialog : public DropWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void requestSongMenu();

protected:
    void showEvent(QShowEvent *);

private:
    void initUI();

private:
    Ui::Dialog *ui;
    NetManager *m_netManager;
    MusicRequest *m_musicRequest;
    ItemList *m_itemList;
    Player *m_player;

    bool m_isPlayListChanged;
    QPair<QString, QStringList> m_currentPlayList;
    int m_currentIndex;
    int m_currentRow;
};

#endif // DIALOG_H
