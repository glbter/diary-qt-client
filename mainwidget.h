#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include "client.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(Client &notesController, QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void handleButton();
    void refreshList(vector<Note> notes);
    void resfreshNoteTextField();
    void saveFile();
    void addedNote(int id);
private:
    void addNote(const string title, const string text);

    Note lastAddedNote;
    QTextEdit *inputFieldNoteText;
    QLineEdit *inputFieldNoteTitle;
    QLineEdit *titleLb;
    QLineEdit *textLb;
    QTextEdit *outputField;

    QListWidget *uiNotes;

    QPushButton *okButton;
    QPushButton *loadFileBtn;

    Client *notesController;
    vector<Note> listNotes;
};


#endif // MAINWIDGET_H
