#pragma once
#ifndef ICLIENT_H
#define ICLIENT_H

#endif // ICLIENT_H
#include "note.h"

#include <iterator>
#include <vector>

class IClient {

public:
    virtual Note& AddNote(const string& title, const  string& text) = 0;
    virtual Note GetNote(const int& id) = 0;
    virtual vector<Note> GetAllNotes() = 0;
    virtual bool Login(const string& login, const string& password) = 0;
    virtual bool isLogined() = 0;
    virtual int CorrectLoginAndPassword(const string& login, const string& password) = 0;
};
