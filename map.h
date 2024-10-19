#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>

class MapItem: public QGraphicsPixmapItem
{
private:
    QMenu *myContextMenu;

public:
    MapItem (QPixmap pixmap, QMenu *contextMenu, QGraphicsItem *parent = nullptr);


protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
};

#endif // MAP_H
