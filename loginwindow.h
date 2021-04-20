#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWindow>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include "iclient.h"
#include <QMainWindow>


class LoginWindow : public QWidget
{
    Q_OBJECT
private slots:
    void loginCommand();
private:
    QLineEdit *inputLoginText;
    QLineEdit *inputLogin;
    QLineEdit *inputPasswordText;
    QLineEdit *inputPassword;

    QPushButton *okButton;

    IClient *controller;

    QMainWindow *parent;
public:
    LoginWindow(QMainWindow *parent, IClient& controller);
    ~LoginWindow();
};

#endif // LOGINWINDOW_H
