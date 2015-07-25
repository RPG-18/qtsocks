#pragma once

#include <QtCore/QObject>

#include <QtNetwork/QTcpSocket>

class Client: public QObject
{
Q_OBJECT

public:

    Client(qintptr socketDescriptor, QObject* parent = 0);

public slots:

    void onRequest();

    void client2world();
    void world2client();

    void sendSocksAnsver();

    void onClientDisconnected();
    void onWorldDisconnected();

private:

    void done();

private:

    QTcpSocket m_client;
    QTcpSocket m_world;
};

