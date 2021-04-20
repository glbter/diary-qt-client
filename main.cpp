#include "loginwindow.h"
#include "mainwindow.h"
#include "notescontroller.h"

#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    INotesController* notesController = new NotesController();
    MainWindow* mw = new MainWindow(*notesController);
    mw->show();
    return a.exec();
}
