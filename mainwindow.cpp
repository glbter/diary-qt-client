#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <qlabel.h>
#include <QList>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <loginwindow.h>
#include <QWidget>
#include "mainwidget.h"

MainWindow::MainWindow(IClient& controller, QWidget *parent)
: QMainWindow(parent)
{
    setWindowTitle("Super-puper schodennyk");
    setGeometry(100, 100, 400, 500);
    setMinimumSize(200, 200);

//    MainWidget* widget = new MainWidget(controller, this);
//    widget->show();
//    MainWindow::setCentralWidget(widget);
    LoginWindow* loginWidget = new LoginWindow(this, controller);
    MainWindow::setCentralWidget(loginWidget);
    loginWidget->show();
}



void MainWindow::openLogin(IClient& controller){
//    LoginWindow* window = new LoginWindow(this, controller);
//    window->show();
    //int res = window->exec();
    //f(res == QDialog::Rejected){
    //    setWindowTitle("pasasi");
    //
    if(controller.isLogined() == false){
        setWindowTitle("pasasi");
    }
    //close();
   // hide();
}

MainWindow::~MainWindow()
{

}
