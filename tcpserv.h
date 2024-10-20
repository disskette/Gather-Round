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
#include <QXmlStreamReader>

//#include "network_subscription.h"
//#include "item.h"
//#include "map.h"
//#include "scene.h"
#include "tcpcli.h"

//! реализовать наблюдателей бля

class Server : public QObject, public Net_subscriber
{
    Q_OBJECT

public:
    Server(Scene *scene, QObject *parent = nullptr);
    void SendInfo(); //! override?
    void deserializeSceneFromXML(const QString &xmlData);

public slots:
    void onReleaseMouseEvent();

private slots:
    void handleNewConnection();

    void readRequest();

    QByteArray serializeSceneToXML();

private:
    QTcpServer *m_server;
    Scene *m_scene;
    QList<QTcpSocket*> m_clients;
};

#endif //TCPSERV_H