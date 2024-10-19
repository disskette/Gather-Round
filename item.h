#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QColor>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Item : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 }; //Для проверки типа в дальнейшем, когда появится sendtoBack/Front
    enum ItemType { Monster, Hero, Weapon };

    Item(ItemType itemType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ItemType itemType() const { return myItemType; }
    QPolygonF polygon() const { return myPolygon; } // Строим фигуру токена (эллипс)
    QPixmap image() const; // Красим (пока без картинки внутри)
    QColor color() const {return myColor;}
    int type() const override { return Type; }
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    ItemType myItemType;
    QPolygonF myPolygon;
    QColor myColor;
    QMenu *myContextMenu;
};

#endif // ITEM_H
