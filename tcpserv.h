#ifndef TCPSERV_H
#define TCPSERV_H

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QNetworkInterface>
#include <QDebug>
#include <QByteArray>
#include <QXmlStreamWriter>

#include "network_subscription.h"
#include "item.h"
#include "map.h"

//! реализовать наблюдателей бля

class Server : public QObject, public Net_subscriber
{
    Q_OBJECT

public:
    Server(QGraphicsScene *scene, QObject *parent = nullptr);
    void SendInfo(); //! override?

private slots:
    void handleNewConnection();

    void readRequest();

    QByteArray serializeSceneToXML();

private:
    QTcpServer *m_server;
    QGraphicsScene *m_scene;
    QList<QTcpSocket*> m_clients;
};

#endif //TCPSERV_H