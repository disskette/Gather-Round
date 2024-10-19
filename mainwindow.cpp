#include "item.h"
#include "scene.h"
#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow()
{
    createActions(); // Привязка методов удаления, закрытия и т.д. в QAction для унификации работы со всеми меню
    createToolBox(); // Меню слева с токенами
    createMenus(); 

    scene = new Scene(itemMenu, this); //Построенное меню работы с объектом полностью добавляется в контекстное меню объекта
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    scene->setBackgroundBrush(Qt::white); //Красим фон белым
    connect(scene, &Scene::itemInserted, this, &MainWindow::itemInserted);
    createToolbars(); 

    grid = new GridItem(50,5000,5000); //Главная сетка
    scene -> addItem(grid);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Gather 'Round"));
}

void MainWindow::buttonGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    const int id = buttonGroup->id(button);

    scene->setItemType(Item::ItemType(id));
    scene->setMode(Scene::InsertItem);
}

void MainWindow::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::itemInserted(Item *item)
{
    scene->setMode(Scene::Mode(Scene::MoveItem));
    buttonGroup->button(int(item->itemType()))->setChecked(false);
}

void MainWindow::pinItem()
{
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
    item->setFlag(QGraphicsItem::ItemIsMovable, false); //нужно добавить действия с тем, что это записывается в xml и передается клиентам
    }
}

void MainWindow::unpinItem()
{
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
    item->setFlag(QGraphicsItem::ItemIsMovable, true); //нужно добавить действия с тем, что это записывается в xml и передается клиентам
    }
}

void MainWindow::hideItem()
{
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
    item->hide(); //нужно добавить действия с тем, что это записывается в xml и передается клиентам, а не прячется у сервера
    }
}

void MainWindow::showItem()
{
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
    item->show(); //нужно добавить действия с тем, что это записывается в xml и передается клиентам, а не появляется у сервера
    }
}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);
    
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Hero"), Item::Hero), 0, 0);
    layout->addWidget(createCellWidget(tr("Monster"), Item::Monster),0, 1);
    layout->addWidget(createCellWidget(tr("Weapon"), Item::Weapon), 1, 0);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Shapes"));
}

void MainWindow::createActions() //TODO: Найти картинки!
{
    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    pinAction = new QAction (QIcon(":/images/pin.png"), tr("Pin"), this);
    connect(pinAction, &QAction::triggered, this, &MainWindow::pinItem);

    unpinAction = new QAction (QIcon(":/images/unpin.png"), tr("Unpin"), this);
    connect(unpinAction, &QAction::triggered, this, &MainWindow::unpinItem);

    hideAction = new QAction (QIcon(":/images/hide.png"), tr("Hide"), this);
    connect(hideAction, &QAction::triggered, this, &MainWindow::hideItem);

    showAction = new QAction (QIcon(":/images/show.png"), tr("Show"), this);
    connect(showAction, &QAction::triggered, this, &MainWindow::showItem);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator(); // Черта горизонтальная для красоты

    itemMenu->addAction(pinAction);
    itemMenu->addAction(unpinAction);
    itemMenu->addAction(hideAction);
    itemMenu->addAction(showAction);
}

void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
}

QWidget *MainWindow::createCellWidget(const QString &text, Item::ItemType type)
{

    Item item(type, itemMenu);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout; 
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
