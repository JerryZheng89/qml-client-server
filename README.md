# Qt client-server
> This project is fork from https://retifrav.github.io/blog/2018/03/08/qt-client-server-qml/.


## What I have done
- fix some bugs in c++ qTCPSocket receive handler
- fix qml singal function, change to javascript function
- and something else

## client
![qml-client](./img/qml-client.png)
## server
![qml-server](./img/qml-server.png)
## Origin REAME

Two GUI-applications, client and server, communicating over network via TCP ([QTcpServer](http://doc.qt.io/qt-5/qtcpserver.html) and [QTcpSocket](http://doc.qt.io/qt-5/qtcpsocket.html)).

Based on Qt and implemented in two ways:

1. [Qt Widgets](https://doc.qt.io/qt-5.10/qtwidgets-index.html) - classic and boring desktop application:

![client-server](./img/widgets-client-server.png "Client-server apps on Qt Widgets")

2. [Qt Quick / QML](https://doc.qt.io/qt-5.10/qtquick-index.html) - a bit more fancy one, to show how Qt Quick applications can rely on C++ backend:

![client-server](./img/qml-client-server.png "Client-server apps on Qt Quick/QML")

More details in the following [article](https://retifrav.github.io/blog/2018/03/08/qt-client-server-qml/).
