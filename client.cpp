#include "client.h"

Client::Client()
{
    this->view = new MainWindow(*this);
}

Note &Client::AddNote(const string &title, const string &text)
{
    return *(new Note());//noteDAO->AddNote(title, text);
}

Note Client::GetNote(const int &id)
{
    return Note();//noteDAO->GetNote(id);
}

vector<Note> Client::GetAllNotes()
{
    return vector<Note>();//noteDAO->GetAllNotes();
}

bool Client::Login(const string &login, const string &password){
    username = login;
    this->password = password;
    logined = true;
    return true;
}


int Client::CorrectLoginAndPassword(const string &login, const string &password){
    return 1;
}

bool Client::isLogined()
{
    return logined;
}
