#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <time.h>

int main(int argc, char *argv[]) {
    std::srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Lights Out");
    w.showMaximized();

    return a.exec();
}
