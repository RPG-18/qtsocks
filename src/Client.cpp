#include <cstdint>

#include <QtCore/QDebug>
#include <QtCore/QtEndian>
#include <QtNetwork/QHostAddress>

#include "Client.h"

namespace
{
#pragma pack(push, 1)
    struct socks4request
    {
        uint8_t version;
        uint8_t command;
        uint16_t port;
        uint32_t address;
        uint8_t end;
    };

    struct socks4ansver
    {
        uint8_t empty = 0;
        uint8_t status;
        uint16_t field1 = 0;
        uint32_t field2 = 0;
    };
#pragma pack(pop)

    enum SocksStatus
    {
        Granted = 0x5a,
        Failed = 0x5b,
        Failed_no_identd = 0x5c,
        Failed_bad_user_id = 0x5d
    };
}
Client::Client(qintptr socketDescriptor, QObject* parent) :
        QObject(parent)
{
    m_client.setSocketDescriptor(socketDescriptor);

    connect(&m_client, &QTcpSocket::readyRead,
            this, &Client::onRequest);

    connect(&m_client,&QTcpSocket::disconnected,
            this, &Client::onClientDisconnected);

    connect(&m_world, &QTcpSocket::connected,
            this, &Client::sendSocksAnsver);

    connect(&m_world, &QTcpSocket::readyRead,
            this, &Client::world2client);

    connect(&m_world,&QTcpSocket::disconnected,
            this, &Client::onWorldDisconnected);
}

void Client::onRequest()
{
    QByteArray request = m_client.readAll();

    socks4request* header = reinterpret_cast<socks4request*>(request.data());

#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    const QHostAddress address(qFromBigEndian(header->address));
#else
    const QHostAddress address(header->address);
#endif

#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    const uint16_t port = qFromBigEndian(header->port);
#else
    const uint16_t port = header->port;
#endif
    //qDebug()<<"connection:"<<address<<"port:"<<port;

    m_world.connectToHost(address, port);

    disconnect(&m_client, &QTcpSocket::readyRead, this,
            &Client::onRequest);

    connect(&m_client, &QTcpSocket::readyRead, this,
            &Client::client2world);
}

void Client::sendSocksAnsver()
{
    socks4ansver ans;
    ans.status = Granted;
    m_client.write(reinterpret_cast<char*>(&ans), sizeof(ans));
    m_client.flush();
}

void Client::client2world()
{
    m_world.write(m_client.readAll());
}

void Client::world2client()
{
    m_client.write(m_world.readAll());
}

void Client::onClientDisconnected()
{
    m_world.flush();

    done();
}

void Client::onWorldDisconnected()
{
    m_client.flush();

    done();
}

void Client::done()
{
    m_client.close();
    m_world.close();

    deleteLater();
}
