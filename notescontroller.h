#pragma once
#ifndef NOTESCONTROLLER_H
#define NOTESCONTROLLER_H
#include "mainwindow.h"
#include "inotescontroller.h"
class NotesController:  public INotesController
{
public:
    NotesController();
    Note& AddNote(const string& title, const  string& text);
    Note GetNote(const int& id) ;
    vector<Note> GetAllNotes();
private:
    MainWindow *view;
};

#endif // NOTESCONTROLLER_H
