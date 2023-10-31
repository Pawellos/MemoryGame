#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setStyleSheet("background-image:url(/Users/pawellos/memoryGame/pics/UEFA-Champions-League.jpeg)");
    w.show();
    return a.exec();
}
