#include "scene.h"
#include "map.h"

#include <QGraphicsSceneMouseEvent>
#include <cmath>


Scene::Scene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent), currentScale(1), offset_changed(false)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = Item::Hero;

    MapItem* map = new MapItem(QPixmap(":/images/dungeon.png"), this->menu());
    map->setPos(2500, 2500);
    addItem(map);
}

void Scene::setMode(Mode mode)
{
    myMode = mode;
}

double& Scene::currScale()
{
    return currentScale;
}

void Scene::setItemType(Item::ItemType type)
{
    myItemType = type;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) return;

    for (QGraphicsItem *item : items()) {
        item->setSelected(false);
    } // Сняли выделение со всех элементов

    QGraphicsItem* unknownItem;

    Item *item;
    switch (myMode) { // Оставим switch на случай, если добавятся ещё режимы
    case InsertItem:
        item = new Item(myItemType, myItemMenu);
        item->setBrush(Qt::transparent);
        item->setPen(QPen(item->color(), 4));
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
    
    case MoveItem:
        unknownItem = itemAt(mouseEvent->scenePos(), QTransform());
        if (unknownItem) unknownItem->setSelected(true); // За раз можно выделить только один объект
        break;

    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();


    if (!selectedItems.isEmpty()) {
        QPointF mousePos = event->scenePos();

        const qreal gridStep = 20;

        // Вычисляем новое положение
        for (QGraphicsItem *item : selectedItems) {
            if(offset_changed==false)
            {
                if(item->type() == Item::Type) offset = event->scenePos() - dynamic_cast<Item*>(item)->pos();
                else if(item->type() == MapItem::Type) offset = event->scenePos() - dynamic_cast<MapItem*>(item)->pos();
                offset_changed = true; // Менять оффсет надо только один раз - сразу же после захвата.
            }
            QPointF newPos(
                round(mousePos.x() / gridStep) * gridStep,
                round(mousePos.y() / gridStep) * gridStep
                );
            QGraphicsItem::GraphicsItemFlags flags = item->flags();
            //Тащим объект не за центр/левый угол, а за точку, где захватили
            if (flags & QGraphicsItem::ItemIsMovable) item->setPos(newPos-offset);
        }
        event->accept();
    }
}


void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    offset_changed=false; // Движение закончили - сняли запрет на изменение оффсета
    emit releaseMouseEventOccurred();
    //qDebug() << "ReleaseMouseEventOccured";
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

