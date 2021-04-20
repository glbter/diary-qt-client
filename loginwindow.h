#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWindow>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include "inotescontroller.h"


class LoginWindow : public QDialog
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

    INotesController *controller;
public:
    LoginWindow(QWidget *parent, INotesController& controller);
    ~LoginWindow();
};

#endif // LOGINWINDOW_H
