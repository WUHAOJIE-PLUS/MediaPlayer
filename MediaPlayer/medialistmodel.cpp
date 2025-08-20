#include "medialistmodel.h"

// MediaListModel.cpp
MediaListModel::MediaListModel(libvlc_media_list_t *mediaList, QObject *parent)
    : QAbstractListModel(parent)
    , _mediaList(mediaList) {
    if (_mediaList)
        libvlc_media_list_retain(_mediaList); // 增加引用计数
}

//播放列表中有几个媒体
int MediaListModel::rowCount(const QModelIndex &parent) const {
    return _mediaList ? libvlc_media_list_count(_mediaList) : 0;
}


QVariant MediaListModel::data(const QModelIndex &index, int role) const {
    if (!_mediaList || !index.isValid())
        return QVariant();

    //表示在这个下标的的媒体是哪个
    libvlc_media_t *media = libvlc_media_list_item_at_index(_mediaList, index.row());
    if (role == Qt::DisplayRole) {
        char *name = libvlc_media_get_meta(media, libvlc_meta_Title);
        return QString(name ? name : "Unknown");
    }
    return QVariant();
}
