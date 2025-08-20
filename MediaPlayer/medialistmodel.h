#ifndef MEDIALISTMODEL_H
#define MEDIALISTMODEL_H

// MediaListModel.h
#include <QAbstractListModel>
#include <vlc/vlc.h>

class MediaListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit MediaListModel(libvlc_media_list_t *mediaList, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    libvlc_media_list_t *_mediaList;
};

#endif // MEDIALISTMODEL_H
