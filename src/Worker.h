#pragma once

#include <QtCore/QObject>

class Worker: public QObject
{
Q_OBJECT

public:

    Q_INVOKABLE void addClient(qintptr socketDescriptor);
};

