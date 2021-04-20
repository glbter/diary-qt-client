#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWindow>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

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


public:
    LoginWindow(QWidget *parent);
    virtual ~LoginWindow() {}
};

#endif // LOGINWINDOW_H
