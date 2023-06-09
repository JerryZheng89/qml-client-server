#include "clientStuff.h"

ClientStuff::ClientStuff(const QString hostAddress, int portNumber) : QObject(), m_nNextBlockSize(0)
{
    status = false;
    tcpSocket = new QTcpSocket();

    host = hostAddress;
    port = portNumber;

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &ClientStuff::connectionTimeout);

    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientStuff::closeConnection);
}

void ClientStuff::connect2host()
{
    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientStuff::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);
}

void ClientStuff::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        //emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
        emit tcpSocket->errorOccurred(QAbstractSocket::SocketTimeoutError);
    }
}

void ClientStuff::connected()
{
    status = true;
    emit statusChanged(status);
}

bool ClientStuff::getStatus() {return status;}

void ClientStuff::readyRead()
{
    QByteArray data = tcpSocket->readAll();
    emit hasReadSome(QString::fromLatin1(data));
}

//void ClientStuff::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void ClientStuff::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
