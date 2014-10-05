#include <QApplication>
#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainController controller;

    return app.exec();
}
