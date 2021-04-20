#include "note.h"
#include <iostream>
#include <iomanip>
Note::Note()
{

}

string Note::getTitle() const
{
    return title;
}

void Note::setTitle(const string &value)
{
    title = value;
}

string Note::getText() const
{
    return text;
}

void Note::setText(const string &value)
{
    text = value;
}

time_t Note::getCreatedDate() const
{
    return createdDate;
}

int Note::getId() const
{
    return id;
}

void Note::setId(int value)
{
    id = value;
}


string Note::ToString()
{
    auto t = getCreatedDate();
    struct tm * curtime = localtime ( &t);
    return  "Title " + getTitle() + "\n" +
            "Text " + getText() + "\n" +
            "Creation Date " + asctime(curtime) + "\n";
}
void Note::Display()
{
    cout<<this->ToString();
}
