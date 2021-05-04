#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWindow>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include "iclient.h"
#include "client.h"
#include <QMainWindow>


class LoginWindow : public QWidget
{
    Q_OBJECT
private slots:
    void loginCommand();
    void loginSuccess();
    void loginFailed();
private:
    QLineEdit *inputLoginText;
    QLineEdit *inputLogin;
    QLineEdit *inputPasswordText;
    QLineEdit *inputPassword;

    QPushButton *okButton;

    Client *controller;

    QMainWindow *parent;
public:
    LoginWindow(QMainWindow *parent, Client& controller);
    ~LoginWindow();
};

#endif // LOGINWINDOW_H
