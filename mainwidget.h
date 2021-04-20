#pragma once
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include "iclient.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(IClient& notesController, QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void handleButton();
    void refreshList();
    void resfreshNoteTextField();
    void saveFile();
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


#endif // MAINWIDGET_H
