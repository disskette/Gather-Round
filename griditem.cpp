#include "griditem.h"

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPainter>

GridItem::GridItem(qreal cellSide,qreal awidth, qreal aheight, QGraphicsItem *parent)
    : QGraphicsItemGroup(parent)
{
    //Горизонтальные линии
    for (int y=0; y<int(aheight); y+=cellSide)
    {
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(0,y,awidth,y);
        lineItem->setPen(QPen(Qt::black, 0.2));
        lineItem ->setZValue(0.2); // Тот же zValue, что и у grid. Только у этих двух объектов zValue=0.2, ни у каких больше быть не может
        addToGroup(lineItem);
    }

    //Вертикальные линии
    for (int x=0; x<int(awidth); x+=cellSide)
    {
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(x,0,x,aheight);
        lineItem->setPen(QPen(Qt::black, 0.2));
        lineItem ->setZValue(0.2);
        addToGroup(lineItem);
    }
    setPos(0,0); //Из верхнего левого угла на всё поле


    setZValue(0.2); //Ниже только карта


    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}



