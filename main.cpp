#include "loginwindow.h"
#include "mainwindow.h"
#include "client.h"

#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IClient* notesController = new Client();
    MainWindow* mw = new MainWindow(*notesController);
    mw->show();
    return a.exec();
}
