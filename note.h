#pragma once
#ifndef NOTE_H
#define NOTE_H
#include <string>
#include <time.h>
using namespace std;

class Note
{
public:
    Note();
    string getTitle() const;
    void setTitle(const string &value);

    string getText() const;
    void setText(const string &value);

    time_t getCreatedDate() const;

    int getId() const;
    void setId(int value);

    void Display();

    string ToString();
private:
    string title;
    string text;
    time_t createdDate = time(NULL);
    int id;
};

#endif // NOTE_H
