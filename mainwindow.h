#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include "client.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client &myclient, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openLogin(Client &controller);
private:

    Client *notesController;

};


#endif // MAINWINDOW_H
