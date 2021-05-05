#include "client.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Client::Client(QObject *parent)     : QObject(parent)
  , m_clientSocket(new QTcpSocket(this))
  , m_loggedIn(false)
{
    //this->view = new MainWindow(*this);
    // Forward the connected and disconnected signals
        connect(m_clientSocket, &QTcpSocket::connected, this, &Client::connected);
        connect(m_clientSocket, &QTcpSocket::disconnected, this, &Client::disconnected);
        // connect readyRead() to the slot that will take care of reading the data in
        connect(m_clientSocket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
        // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
       // connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);
        // Reset the m_loggedIn variable when we disconnec. Since the operation is trivial we use a lambda instead of creating another slot
        connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});

//                QString::fromStdString("/localhost")
        //QHostAddress *address;
        //address->setAddress(QStringLiteral("127.0.0.1"));
        //m_clientSocket->connectToHost(address, 5555);
        m_clientSocket->connectToHost("127.0.0.1", 5555);
}

Note &Client::AddNote(const string &title, const string &text)
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;

    message[ACTION] = ADD_NOTE_ACTION;

    message[LOGIN] = QString::fromStdString(username);
    message[PASSWORD] = QString::fromStdString(password);

    QJsonObject data;
    message[QStringLiteral("Title")] = QString::fromStdString(title);
    message[QStringLiteral("Text")] = QString::fromStdString(text);
    message[DATA] = data;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();

    return *(new Note());//noteDAO->AddNote(title, text);
}

Note Client::GetNote(const int &id)
{    
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[ACTION] = GET_NOTE_ACTION;
    message[LOGIN] = QString::fromStdString(username);
    message[PASSWORD] = QString::fromStdString(password);

    QJsonObject data;
    message[QStringLiteral("NoteId")] = QString::number(id);
    message[DATA] = data;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();

    return Note();//noteDAO->GetNote(id);
}

vector<Note> Client::GetAllNotes()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[ACTION] = GET_ALL_NOTES_ACTION;
    message[DATA] = "";
    message[LOGIN] = QString::fromStdString(username);
    message[PASSWORD] = QString::fromStdString(password);

    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();

    return vector<Note>();//noteDAO->GetAllNotes();
}

bool Client::Login(const string &login, const string &password){
    username = login;
    this->password = password;

    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);
        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);
        // Create the JSON we want to send
        QJsonObject message;
        message[ACTION] = LOGIN_ACTION;
        message[DATA] = "";
        message[LOGIN] = QString::fromStdString(username);
        message[PASSWORD] = QString::fromStdString(password);
        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }

    logined = true;
    return true;
}


int Client::CorrectLoginAndPassword(const string &login, const string &password){
    Login(login, password);
    return 1;
}

bool Client::isLogined()
{
    return logined;
}


void Client::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void Client::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("ResponseType"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it

    if (typeVal.toString().compare(LOGIN_ACTION)) { //It's a login message
        if (m_loggedIn)
            return; // if we are already logged in we ignore

        const int userId = docObj.value(QLatin1String("UserId")).toInt();
        if(userId > 0) {
            m_loggedIn = true;
            emit loggedIn();
            return;
        }
        emit loginFail();

    } else if (typeVal.toString().compare(GET_ALL_NOTES_ACTION)) {
        return;
    } else if (typeVal.toString().compare(ADD_NOTE_ACTION)) {
        const int noteId = docObj.value(QLatin1String("NoteId")).toInt();
        emit noteAdded(noteId);
        return;
    } else if (typeVal.toString().compare(GET_NOTE_ACTION)) {
        const int id = docObj.value(QLatin1String("NoteId")).toInt();
        const string text = docObj.value(QLatin1String("Text")).toString().toStdString();
        const string title = docObj.value(QLatin1String("Text")).toString().toStdString();
        Note note;
        note.setId(id);
        note.setTitle(title);
        note.setText(text);
        emit noteGetted(note);
        return;
    }
    // the login attempt failed, we extract the reason of the failure from the JSON
    // and notify it via the loginError signal
    const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
    emit loginError(reasonVal.toString());
    return;
}



void Client::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}
