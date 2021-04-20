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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IClient& notesController, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleButton();
    void refreshList();
    void resfreshNoteTextField();
    void saveFile();
    void openLogin(IClient& controller);
private:
    QTextEdit *inputFieldNoteText;
    QLineEdit *inputFieldNoteTitle;
    QLineEdit *titleLb;
    QLineEdit *textLb;
    QTextEdit *outputField;

    QListWidget *uiNotes;

    QPushButton *okButton;
    QPushButton *loadFileBtn;

    IClient *notesController;
    vector<Note> listNotes;
};
#endif // MAINWINDOW_H
