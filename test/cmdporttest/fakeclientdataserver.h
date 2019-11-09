#ifndef FAKECLIENTDATASERVER_H
#define FAKECLIENTDATASERVER_H

#include <QObject>

class FakeClientDataServer : public QObject
{
    Q_OBJECT
public:
    explicit FakeClientDataServer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FAKECLIENTDATASERVER_H
