#include "mainwindow.h"

#include <QApplication>

int main(int argv, char *args[])
{
    Q_INIT_RESOURCE(scene);

    QApplication app(argv, args);
    MainWindow mainWindow;
    mainWindow.setGeometry(100, 100, 1000, 500);
    mainWindow.show();

    return app.exec();
}
