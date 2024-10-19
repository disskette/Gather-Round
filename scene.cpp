#include "scene.h"

#include <QGraphicsSceneMouseEvent>

Scene::Scene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = Item::Hero;
}

void Scene::setMode(Mode mode)
{
    myMode = mode;
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

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}