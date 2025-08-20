#include "playlistdialog.h"


PlaylistDialog::PlaylistDialog(libvlc_media_list_t *mediaList, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("播放列表");

    this->resize(120,200);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

    this->setStyleSheet("color:white");

    _model = new MediaListModel(mediaList, this);
    _listView = new QListView(this);
    _listView->setModel(_model);

    connect(_listView, &QListView::clicked, [this](const QModelIndex &index){
        emit itemSelected(index.row());
        this->close();
    });
}

void PlaylistDialog::is_close(){
    this->close();
}
