#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QObject>
#include <QWidget>

class serverSocket : public QObject
{
    Q_OBJECT
public:
    serverSocket(QWidget* parent);
    void connectToSerever(QString ip);
    static QTcpSocket* serverClient;

public slots:
    void myReadReady();

    void myConnected();

    void myDisconnect();

signals:
    void refreshOrders(qint16 orderNo);

private:
    QWidget* myParent;
};

#endif // SERVERSOCKET_H
