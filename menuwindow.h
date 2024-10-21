#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "item.h"
#include "mainwindow.h"

//! [0]
class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow();

private slots:
    void startMaster(const QString &roomId);  // Запуск MainWindow с ролью Master
    void startPlayer(const QString &roomId);  // Запуск MainWindow с ролью Player
    void openIdDialog(bool isMaster);

private:
    QPushButton *createRoomButton;
    QPushButton *joinRoomButton;
};
//! [0]

#endif // MENUWINDOW_H
