#include "dialog.h"
#include "ui_dialog.h"
#include "request.h"
#include "response.h"
#include "itemlist.h"
#include "player.h"
#include "netmanager.h"
#include <QtWidgets>
#include <QtWidgets>

static int s_role_itemId = Qt::UserRole + 1;

Dialog::Dialog(QWidget *parent)
    : DropWidget(parent)
    , ui(new Ui::Dialog)
    , m_isPlayListChanged(false)
    , m_currentRow(0)
{
    ui->setupUi(this);
    m_netManager = new NetManager(this);
    m_musicRequest = new MusicRequest(8009, "1aab66c68a95442abb06d999093fcd12", this);
    m_itemList = new ItemList(this);
    m_player = new Player(this);

    connect(ui->pbClose, &QPushButton::clicked, [this]() {
        this->close();
    });

    connect(ui->pbPlay, &QPushButton::clicked, [this]() {
        QMediaPlayer::State currentState = m_player->state();
        if (m_isPlayListChanged) {
            m_player->setPlayList(m_currentPlayList.second);
        }
        if (m_player->index() != m_currentIndex) {
            m_player->setIndex(m_currentIndex);
        }

        if (currentState != QMediaPlayer::PlayingState) {
            m_player->play();
        } else {
            m_player->pause();
        }

        ui->pbPlay->setText(QMediaPlayer::PlayingState == m_player->state() ? tr("pause") : tr("play"));
    });

    connect(ui->itemList, &QListWidget::doubleClicked, [this](const QModelIndex &index) {
        if (m_currentRow != index.row()) {
            m_currentRow = index.row();
            requestSongMenu();
        }
    });

    connect(ui->lwSongList, &QListWidget::doubleClicked, [this](const QModelIndex &index) {
        m_currentIndex = index.row();
        if (index.row() == m_player->index()) {
            if (m_player->state() == QMediaPlayer::PlayingState) {
                m_player->stop();
            } else {
                emit ui->pbPlay->clicked();
            }
        } else {
            emit ui->pbPlay->clicked();
        }
    });

    connect(ui->pageWidget, &PageNumberWidget::sigPageChanged, [this](int pageNumber) {
        requestSongMenu();
    });

    initUI();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::requestSongMenu()
{
    int currentId = ui->itemList->currentItem()->data(s_role_itemId).toInt();
    m_musicRequest->setItemId(currentId);
    int currentPage = ui->pageWidget->currentPage();
    m_musicRequest->setPage(currentPage);

    m_netManager->request(m_musicRequest->getUrl(), [this](const QByteArray &data) {
        MusicResponse response(data);
        if (response.resCode() == 0) {
            const PageBean& pageBean = response.pageBean();
            ui->labelTitle->setText(pageBean.title);
            ui->labelPic->setText(pageBean.picUrl);
            qDebug() << pageBean.picUrl;

            const QList<Song> songs = response.songList();
            ui->lwSongList->clear();

            m_isPlayListChanged = (pageBean.title != m_currentPlayList.first);
            m_currentPlayList.first = pageBean.title;
            m_currentPlayList.second.clear();
            for (auto iter = songs.begin(); iter != songs.end(); ++iter) {
                ui->lwSongList->addItem(iter->songname + " - " + iter->singername + " [" + iter->albumname + "]");
                m_currentPlayList.second.append(iter->url);
            }
            ui->pageWidget->setCount(pageBean.totalPage);
        } else {
            qDebug() << response.resError();
        }
    });
}

void Dialog::showEvent(QShowEvent *)
{
    const QMap<int, QString> & itemList = m_itemList->data();
    int row = 0;
    for (auto iter = itemList.begin(); iter != itemList.end(); ++iter) {
        ui->itemList->addItem(iter.value());
        ui->itemList->item(row++)->setData(s_role_itemId, iter.key());
    }

    ui->itemList->setCurrentRow(0);
    static bool once = true;
    if (once) {
        once = false;
        requestSongMenu();
    }
}

void Dialog::initUI()
{
    this->setBackground(QImage(":/images/ou_mei"));

    QPixmap closePixmap = QPixmap(":/images/close");
    QPixmap playPixmap = QPixmap(":/images/play").scaled(50, 50);
    QPixmap prevPixmap = QPixmap(":/images/prev").scaled(40, 40);
    QPixmap nextPixmap = QPixmap(":/images/next").scaled(40, 40);

    ui->pbClose->setImages(closePixmap, closePixmap, closePixmap);
    ui->pbPlay->setImages(playPixmap, playPixmap, playPixmap);
    ui->pbPrev->setImages(prevPixmap, prevPixmap, prevPixmap);
    ui->pbNext->setImages(nextPixmap, nextPixmap, nextPixmap);
}
