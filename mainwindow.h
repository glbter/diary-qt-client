#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include "inotescontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(INotesController& notesController, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleButton();
    void refreshList();
    void resfreshNoteTextField();
    void saveFile();
    void openWidget();
private:
    QTextEdit *inputFieldNoteText;
    QLineEdit *inputFieldNoteTitle;
    QLineEdit *titleLb;
    QLineEdit *textLb;
    QTextEdit *outputField;
    QCalendarWidget *calendar;
    QListWidget *uiNotes;
    INotesController *notesController;
    vector<Note> listNotes;
};
#endif // MAINWINDOW_H
