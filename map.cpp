#include "map.h"

#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

MapItem::MapItem (QPixmap pixmap, QMenu *contextMenu, QGraphicsItem *parent):
    QGraphicsPixmapItem (parent), myContextMenu (contextMenu)
{
    this->setPixmap(pixmap);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void MapItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
