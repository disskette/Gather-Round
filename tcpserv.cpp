#include "tcpserv.h"

//! реализовать наблюдателей бля

Server::Server(QGraphicsScene *scene, QObject *parent) 
        : QObject(parent), m_scene(scene)
    {
        m_server = new QTcpServer(this);
        connect(m_server, &QTcpServer::newConnection, this, &Server::handleNewConnection);
        if (!m_server->listen(QHostAddress::Any, 5702)) {
            qDebug() << "Server could not start!";
        } else {
            qDebug() << "Server started on port 5702";
        }
    }

void Server::handleNewConnection()
    {
        QTcpSocket *clientSocket = m_server->nextPendingConnection();
        m_clients.append(clientSocket);
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readRequest);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        qDebug() << "New client connected!";
    }

void Server::SendInfo()
{
//!
}

void Server::readRequest()
    {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        QByteArray request = clientSocket->readAll();
        
        if (request.trimmed() == "GET_ITEMS") {
            qDebug() << "Get_items command";
            QByteArray xmlData = serializeSceneToXML();
            clientSocket->write(xmlData);
            clientSocket->disconnectFromHost();
        }
    }

QByteArray Server::serializeSceneToXML() //! понять как копировать состояние в начале
    {
        QByteArray xmlData;
        QXmlStreamWriter xmlWriter(&xmlData);
        
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("SceneItems");

        // Iterate through all items in the scene
        foreach (QGraphicsItem *item, m_scene->items()) {
            xmlWriter.writeStartElement("Item");
            xmlWriter.writeAttribute("type", item->type() == QGraphicsItem::UserType ? "Custom" : "Standard");
            xmlWriter.writeTextElement("PosX", QString::number(item->pos().x()));
            xmlWriter.writeTextElement("PosY", QString::number(item->pos().y()));
            // Add more properties as needed
            xmlWriter.writeEndElement(); // End Item
        }

        xmlWriter.writeEndElement(); // End SceneItems
        xmlWriter.writeEndDocument();

        return xmlData;
    }

