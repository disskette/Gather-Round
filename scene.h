#ifndef SCENE_H
#define SCENE_H

#include "item.h"

#include <QGraphicsScene>
#include <QDebug>


QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
QT_END_NAMESPACE

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, MoveItem };

    explicit Scene(QMenu *itemMenu, QObject *parent = nullptr);

    double& currScale();

    QMenu* menu(){return myItemMenu;}

public slots:
    void setMode(Mode mode);
    void setItemType(Item::ItemType type);

signals:
    void itemInserted(Item *item);
    void itemSelected(QGraphicsItem *item);
    void releaseMouseEventOccurred(); //!new

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Item::ItemType myItemType;
    QMenu *myItemMenu; //Меню для работы с объектом одинаково для всех объектов
    Mode myMode;

    double currentScale;

    QPointF offset; // Смещение между позицией курсора и позицией элемента
    bool offset_changed; //Выставлено ли уже смещение
};

#endif // SCENE_H
