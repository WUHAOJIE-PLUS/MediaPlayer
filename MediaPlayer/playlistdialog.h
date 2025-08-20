#ifndef PLAYLISTDIALOG_H
#define PLAYLISTDIALOG_H

#include <QDialog>
#include <QListView>
#include "MediaListModel.h"


//播放列表对话框
class PlaylistDialog : public QDialog {
    Q_OBJECT
public:
    explicit PlaylistDialog(libvlc_media_list_t *mediaList, QWidget *parent = nullptr);
    void is_close();
signals:
    void itemSelected(int index);

private:
    QListView *_listView;
    MediaListModel *_model;
};

#endif // PLAYLISTDIALOG_H
