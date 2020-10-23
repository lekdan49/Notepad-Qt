#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // handles widgets, events, mouse movements
    MainWindow w;               // creates the main application object
    w.show();                   // displays the main application object
    return a.exec();            // puts the application into a loop
}
