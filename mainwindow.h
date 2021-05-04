#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include "iclient.h"
#include "client.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client& notesController, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openLogin(IClient& controller);
private:

    IClient *notesController;

};
#endif // MAINWINDOW_H
