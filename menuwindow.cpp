#include "menuwindow.h"
#include "mainwindow.h"
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include "tcpserv.h"

// Конструктор MenuWindow
MenuWindow::MenuWindow() {
    // Создаём кнопки
    createRoomButton = new QPushButton("Создать комнату", this);
    joinRoomButton = new QPushButton("Подключиться к комнате", this);

    // Устанавливаем положение и размер кнопок
    createRoomButton->setGeometry(50, 50, 200, 50);
    joinRoomButton->setGeometry(50, 120, 200, 50);

    // Подключаем сигналы к лямбда-функциям
    connect(createRoomButton, &QPushButton::clicked, this, [this]() {
        openIdDialog(true);  // Диалог для создания комнаты (Master)
    });

    connect(joinRoomButton, &QPushButton::clicked, this, [this]() {
        openIdDialog(false);  // Диалог для подключения (Player)
    });
}

// Открывает диалог для ввода ID комнаты
void MenuWindow::openIdDialog(bool isMaster) {
    QDialog dialog(this);
    dialog.setWindowTitle(isMaster ? "Создать комнату" : "Подключиться к комнате");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLineEdit *idInput = new QLineEdit(&dialog);
    idInput->setPlaceholderText("Введите ID комнаты");
    layout->addWidget(idInput);

    QPushButton *submitButton = new QPushButton("Ввести", &dialog);
    layout->addWidget(submitButton);

    QPushButton *connectButton = new QPushButton("Подключиться", &dialog);
    layout->addWidget(connectButton);

    // Обработка нажатия
    connect(submitButton, &QPushButton::clicked, [&]() {
        QString roomId = idInput->text();  // Получаем ID комнаты

        if (isMaster) {
            startMaster(roomId);  // Переход на MainWindow с ролью Master
        } else {
            startPlayer(roomId);  // Переход на MainWindow с ролью Player
        }
        dialog.accept();  // Закрываем диалог
    });

    // "Подключиться" просто закрывает диалог
    connect(connectButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

// Запуск MainWindow с ролью Master
void MenuWindow::startMaster(const QString &roomId) {
    MainWindow *mainWindow = new MainWindow(MainWindow::Master, roomId);
    mainWindow->show();
    this->close();
}


// Запуск MainWindow с ролью Player
void MenuWindow::startPlayer(const QString &roomId) {
    MainWindow *mainWindow = new MainWindow(MainWindow::Player, roomId);
    mainWindow->show();
    this->close();
}
