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
    this->view = new MainWindow(*this);
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
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("request")] = QString::fromStdString("addNote");
    message[QStringLiteral("title")] = QString::fromStdString(title);
    message[QStringLiteral("text")] = QString::fromStdString(text);

    message[QStringLiteral("username")] = QString::fromStdString(username);
    message[QStringLiteral("passwork")] = QString::fromStdString(password);
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();

    return *(new Note());//noteDAO->AddNote(title, text);
}

Note Client::GetNote(const int &id)
{    
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
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("request")] = QString::fromStdString("getAll");

    message[QStringLiteral("username")] = QString::fromStdString(username);
    message[QStringLiteral("passwork")] = QString::fromStdString(password);
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
        message[QStringLiteral("type")] = QStringLiteral("login");
        message[QStringLiteral("request")] = QString::fromStdString("login");
        message[QStringLiteral("username")] = QString::fromStdString(username);
        message[QStringLiteral("password")] = QString::fromStdString(password);
        // send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }

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







//void Client::login(const QString &userName)
//{
//    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
//        // create a QDataStream operating on the socket
//        QDataStream clientStream(m_clientSocket);
//        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
//        clientStream.setVersion(QDataStream::Qt_5_7);
//        // Create the JSON we want to send
//        QJsonObject message;
//        message[QStringLiteral("type")] = QStringLiteral("login");
//        message[QStringLiteral("username")] = userName;
//        // send the JSON using QDataStream
//        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
//    }
//}

void Client::sendMessage(const QString &text)
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = text;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void Client::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void Client::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        if (m_loggedIn)
            return; // if we are already logged in we ignore
        // the success field will contain the result of our attempt to login
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return; // the message had no success field so we ignore
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            // we logged in succesfully and we notify it via the loggedIn signal
            emit loggedIn();
            return;
        }
        // the login attempt failed, we extract the reason of the failure from the JSON
        // and notify it via the loginError signal
        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) { //It's a chat message
        // we extract the text field containing the chat text
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        // we extract the sender field containing the username of the sender
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        if (senderVal.isNull() || !senderVal.isString())
            return; // the sender field was invalid so we ignore
        // we notify a new message was received via the messageReceived signal
        emit messageReceived(senderVal.toString(), textVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        emit userJoined(usernameVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat
         // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        emit userLeft(usernameVal.toString());
    }
}

//void Client::connectToServer(const QHostAddress &address, quint16 port)
//{

//}

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
