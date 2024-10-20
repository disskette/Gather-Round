#include "mainwindow.h"
#include "menuwindow.h"

#include <QApplication>

int main(int argv, char *args[])
{
    Q_INIT_RESOURCE(scene);

    QApplication app(argv, args);
    MenuWindow menuWindow;
    menuWindow.setGeometry(100, 100, 1000, 500);
    menuWindow.show();

    return app.exec();
}
