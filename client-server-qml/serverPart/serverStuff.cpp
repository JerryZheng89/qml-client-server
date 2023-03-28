#include "serverStuff.h"

ServerStuff::ServerStuff() : QObject(), m_nNextBlockSize(0)
{
    tcpServer = new QTcpServer();
}

QList<QTcpSocket *> ServerStuff::getClients()
{
    return clients;
}

void ServerStuff::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerStuff::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerStuff::gotDisconnection);

    clients << clientSocket;

    sendToClient(clientSocket, "Reply: connection established");
}

void ServerStuff::readClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    QByteArray data = clientSocket->readAll();

    qDebug() << "received message";

    emit gotNewMesssage(QString::fromLatin1(data));

    if (sendToClient(clientSocket, QString("Reply: received [%1]").arg(QString::fromLatin1(data))) == -1)
    {
        qDebug() << "Some error occured";
    }
}

void ServerStuff::gotDisconnection()
{
    clients.removeAt(clients.indexOf((QTcpSocket*)sender()));
    emit smbDisconnected();
}

qint64 ServerStuff::sendToClient(QTcpSocket *socket, const QString &str)
{
    return socket->write(str.toLatin1());
}
