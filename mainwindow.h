#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "item.h"
#include "griditem.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include "tcpserv.h"

class Scene;
QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QButtonGroup;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum Role { Master, Player };
    explicit MainWindow(Role role, const QString &roomId, QWidget *parent = nullptr);
private slots:
    void buttonGroupClicked(QAbstractButton *button); // Кликаем по кнопке-токену из toolbox`а
    void itemInserted(Item *item);
    //Все действия с удалением/закрепление/деланием невидимым только для сервера
    void deleteItem();
    void pinItem();
    void unpinItem();
    void zoomIn();
    void zoomOut();
private:
    void createToolBox(); 
    void createActions(); // Привязать все QAction к методам
    void createMenus(); // Создать fileMenu и itemMenu
    void createToolbars();
    QWidget *createCellWidget(const QString &text, Item::ItemType type); // Виджет токена в toolbox
    Scene *scene;
    QGraphicsView *view;
    
    QAction *exitAction;

    QAction *addAction;
    QAction *deleteAction;
    QAction *pinAction;
    QAction *unpinAction;
    QAction* zoomInAction;
    QAction* zoomOutAction;

    QMenu *fileMenu; // Меню действий с файлом (приложением): закрыть. Потенциал на сохранения состояния карты
    QMenu *itemMenu; // Меню действий с объектом: удалить, закрепить...

    QToolBar *editToolBar; // Находится под File, Item в окне приложения

    QToolBox *toolBox; // Меню слева

    QButtonGroup *buttonGroup; // Кнопки-токены из toolbox

    GridItem* grid; // Главная сетка 

    Role currentRole;  // Хранит роль пользователя
    QString roomId;

    //void setupUI(QVBoxLayout *parentLayout);    // Метод для настройки интерфейса в зависимости от роли
};
#endif // MAINWINDOW_H