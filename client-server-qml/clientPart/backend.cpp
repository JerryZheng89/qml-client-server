#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent) : QObject(parent)
{
    client = new ClientStuff("172.16.81.29", 6547);

    //setStatus(client->get_status());

    connect(client, &ClientStuff::hasReadSome, this, &Backend::receivedSomething);
    connect(client, &ClientStuff::statusChanged, this, &Backend::setStatus);
    // FIXME change this connection to the new syntax
    connect(client->tcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));
}

bool Backend::getStatus()
{
    return client->getStatus();
}

void Backend::setStatus(bool newStatus)
{
    //qDebug() << "new status is:" << newStatus;
    if (newStatus)
        { emit statusChanged("CONNECTED"); }
    else
        { emit statusChanged("DISCONNECTED"); }
}

void Backend::receivedSomething(QString msg)
{
    qDebug()<<"recevied:\n"<< msg;
    emit someMessage(msg);
}

void Backend::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }

    emit someError(strError);
}

void Backend::connectClicked()
{
    client->connect2host();
}

void Backend::sendClicked(QString msg)
{
    client->tcpSocket->write(msg.toLatin1());
}

void Backend::disconnectClicked()
{
    client->closeConnection();
}
