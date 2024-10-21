#include "item.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

Item::Item(ItemType itemType,QMenu* ContextMenu,
                         QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent), myItemType(itemType), myContextMenu(ContextMenu)
{
    QPainterPath path;
    switch (myItemType) {
    case Monster:
        myColor = Qt::red;
        path.addEllipse(QPointF(0, 0), 20, 20); //размеры потом поменяем на основе размеров сетки
        myPolygon = path.toFillPolygon();
        break;
    case Hero:
        myColor = Qt::green;
        path.addEllipse(QPointF(0, 0), 10, 10);
        myPolygon = path.toFillPolygon();
        break;
    default:
        myColor = Qt::blue;
        path.addEllipse(QPointF(0, 0), 5, 5);
        myPolygon = path.toFillPolygon();
        break;
    }
    setPolygon(myPolygon);

    setZValue(0.3); //Всегда выше сетки и карты
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QPixmap Item::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(myColor, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}

void Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}


