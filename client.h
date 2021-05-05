#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include "note.h"
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class QJsonDocument;
using namespace std;

class Client: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Client)
public:
    explicit Client(QObject *parent = nullptr);
    Note& AddNote(const string& title, const  string& text);
    Note GetNote(const int& id) ;
    vector<Note> GetAllNotes();

    bool Login(const string& login, const string& password);
    int CorrectLoginAndPassword(const string& login, const string& password);
    bool isLogined();

private:
    bool logined = false;
    string username;
    string password;




public slots:
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void loginFail();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);

    void noteGetted(const Note& note);
    void noteAdded(const int noteId);
    void allNotesReceived(vector<Note> notes);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);

    QString LOGIN = QStringLiteral("Login");
    QString PASSWORD = QStringLiteral("Password");
    QString ACTION = QStringLiteral("Action");
    QString DATA = QStringLiteral("Data");

    QString LOGIN_ACTION = QStringLiteral("Login");
    QString ADD_NOTE_ACTION = QStringLiteral("AddNote");
    QString GET_ALL_NOTES_ACTION = QStringLiteral("GetAllUserNotes");
    QString GET_NOTE_ACTION = QStringLiteral("GetNotes");
};

#endif // CLIENT_H
