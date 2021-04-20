#include "notescontroller.h"

NotesController::NotesController()
{
    this->view = new MainWindow(*this);
}

Note &NotesController::AddNote(const string &title, const string &text)
{
    return *(new Note());//noteDAO->AddNote(title, text);
}

Note NotesController::GetNote(const int &id)
{
    return Note();//noteDAO->GetNote(id);
}

vector<Note> NotesController::GetAllNotes()
{
    return vector<Note>();//noteDAO->GetAllNotes();
}
