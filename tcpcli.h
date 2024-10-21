#ifndef TCPCLI_H
#define TCPCLI_H

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QXmlStreamReader>

#include "network_subscription.h"
#include "item.h"
#include "map.h"
#include "scene.h"

class Client : public QObject
{
    Q_OBJECT

private:
    Scene *m_scene;


public:
    //Client(const QString &subnet, quint16 port, QObject *parent = nullptr);
    Client(Scene *scene, QObject *parent = nullptr);
    QTcpSocket *socket;
    void deserializeSceneToXML();

private slots:
    void sendInfo(); //override?
    void onReadyRead();
    void deserializeSceneFromXML(const QString &xmlData);
    void onDisconnected();




    
};

#endif //TCPCLI_H