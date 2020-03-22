#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QObject>
#include <QWidget>

class serverSocket : public QObject
{
public:
    serverSocket(QWidget* parent);
    void connectToSerever(QString ip);
    static QTcpSocket* serverClient;

public slots:
    void myReadReady();

    void myConnected();

    void myDisconnect();


private:
    QWidget* myParent;
    enum ALLAction{kitchenInfo = 101};
};

#endif // SERVERSOCKET_H
