#include "scene.h"
#include "map.h"

#include <QGraphicsSceneMouseEvent>
#include <cmath>


Scene::Scene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent), currentScale(1)
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
    if (mouseEvent->button() != Qt::LeftButton)
        return;

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

        // Вычисляем новое положение с привязкой к сетке
        for (QGraphicsItem *item : selectedItems) {
            QPointF newPos(
                round(mousePos.x() / gridStep) * gridStep,
                round(mousePos.y() / gridStep) * gridStep
                );
            item->setPos(newPos);
        }
        event->accept();
    }
}


void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit releaseMouseEventOccurred();

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

