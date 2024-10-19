#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItemGroup>


//Можно и не делать отдельный класс мб, но так нагляднее, как по мне
class GridItem : public QGraphicsItemGroup
{
public:
    enum { Type = UserType + 16 }; //Для проверки типа в дальнейшем, когда появится sendtoBack/Front

    explicit GridItem(qreal cellSide,qreal awidth, qreal aheight, QGraphicsItem *parent = nullptr); //первый аргумент - сторона клетки; ширина и высота совпадают с параметрами сцены

private:
};


#endif // GRIDITEM_H
