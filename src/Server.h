#pragma once

#include <QtCore/QVector>

#include <QtNetwork/QTcpServer>

class Worker;
class QThread;

class Server: public QTcpServer
{
Q_OBJECT

public:

    Server(size_t threads = 4, QObject * parent = nullptr);
    ~Server();

protected:

    virtual void incomingConnection(qintptr socketDescriptor);

private:

    void initThreads();

private:

    size_t m_threadCount;

    QVector<QThread*> m_threads;
    QVector<Worker*> m_workers;
    size_t m_rrcounter;
};

