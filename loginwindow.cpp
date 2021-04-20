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


LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Login");
    setGeometry(100, 100, 400, 500);
    setMinimumSize(200, 200);
    int paddingX = 10;
    int paddingY = 10;

    inputLoginText = new QLineEdit("Login", this);
    inputLoginText->setGeometry(paddingX, paddingY, 60, 20);
    inputLoginText->setReadOnly(true);

    inputLogin = new QLineEdit(this);
    inputLogin->setGeometry(paddingX, paddingY+30, 100, 20);

    inputPasswordText = new QLineEdit("Login", this);
    inputPasswordText->setGeometry(paddingX, paddingY+60, 60, 20);
    inputPasswordText->setReadOnly(true);

    inputPassword = new QLineEdit(this);
    inputPassword->setGeometry(paddingX, paddingY+90, 100, 20);

    QPushButton *okButton = new QPushButton("Login", this);
    okButton->setGeometry(paddingX, paddingY+120, 35, 20);
    connect(okButton, SIGNAL(released()), this, SLOT(loginCommand()));
}

void LoginWindow::loginCommand(){
    std::string login = inputLogin->text().toUtf8().constData();
    std::string password = inputPassword->text().toUtf8().constData();
    if(true){
        close();
    }
}
