#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include "mainwindow.h"
#include "iclient.h"
using namespace std;

class Client: public IClient
{
public:
    Client();
    Note& AddNote(const string& title, const  string& text);
    Note GetNote(const int& id) ;
    vector<Note> GetAllNotes();

    bool Login(const string& login, const string& password);
    int CorrectLoginAndPassword(const string& login, const string& password);
    bool isLogined();

private:
    MainWindow *view;
    bool logined = false;
    string username;
    string password;
};

#endif // CLIENT_H
