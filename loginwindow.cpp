#include "loginwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <qlabel.h>
#include <QList>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <QDialog>
#include "inotescontroller.h"



LoginWindow::LoginWindow(QWidget *parent, INotesController& controller) : QDialog(parent)
{
    setWindowTitle("Login");
    setGeometry(100, 100, 400, 500);
    setMinimumSize(200, 200);
    int paddingX = 10;
    int paddingY = 10;

    this->controller = &controller;

    inputLoginText = new QLineEdit("Username", this);
    inputLoginText->setGeometry(paddingX, paddingY, 60, 20);
    inputLoginText->setReadOnly(true);

    inputLogin = new QLineEdit(this);
    inputLogin->setGeometry(paddingX, paddingY+30, 100, 20);

    inputPasswordText = new QLineEdit("Password", this);
    inputPasswordText->setGeometry(paddingX, paddingY+60, 60, 20);
    inputPasswordText->setReadOnly(true);

    inputPassword = new QLineEdit(this);
    inputPassword->setGeometry(paddingX, paddingY+90, 100, 20);

    okButton = new QPushButton("Log in", this);
    okButton->setGeometry(paddingX, paddingY+120, 35, 20);
    connect(okButton, SIGNAL(released()), this, SLOT(loginCommand()));
}

void LoginWindow::loginCommand(){
    std::string login = inputLogin->text().toUtf8().constData();
    std::string password = inputPassword->text().toUtf8().constData();
    if(controller->Login(login, password)){
        close();
    }
}

LoginWindow::~LoginWindow(){
    delete inputLoginText;
    delete inputLogin;
    delete inputPasswordText;
    delete inputPassword;

    delete okButton;
}
