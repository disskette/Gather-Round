#include "tcpserv.h"


//! реализовать наблюдателей бля

Server::Server(Scene *scene, QObject *parent) 
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
        //!
        m_clients.append(clientSocket);
        //!
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readRequest);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        qDebug() << "New client connected!";
    }

void Server::onReleaseMouseEvent()
{
    qDebug() << m_clients.size();
    for (QTcpSocket* cli : m_clients)
    {
        qDebug() << "ANANAS";
        QByteArray xmlData = serializeSceneToXML();
        qDebug() << "ANANANAS";
        cli->write(xmlData);
        qDebug() << "ANANANANAS";
    }

}

void Server::SendInfo()
{
   
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

QByteArray Server::serializeSceneToXML()
    {
        QByteArray xmlData;
        QXmlStreamWriter xmlWriter(&xmlData);
        
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("SceneItems");


        Item* circle;
        Item::ItemType type;

        // Iterate through all items in the scene
        foreach (QGraphicsItem *item, m_scene->items()) {
            if (!(item->pos().x() == 0 && item->pos().y() == 0)){
                xmlWriter.writeStartElement("Item");

                if(item->type()==Item::Type) //Обнаружили кружок //V
                {
                    circle = dynamic_cast<Item*>(item); //Достали кружок. Можем работать
                    type = circle -> Item::itemType(); //Достали тип кружочка

                    switch (type){
                        case Item::ItemType::Hero:
                            xmlWriter.writeTextElement("type", "Hero");
                            break;
                        case Item::ItemType::Monster:
                            xmlWriter.writeTextElement("type", "Monster");
                            break;
                        case Item::ItemType::Weapon:
                            xmlWriter.writeTextElement("type", "Weapon");
                            break;
                        default:
                            xmlWriter.writeTextElement("type", "Unknown");
                            break;
                    }
                    

                }

                else if(item->type()==MapItem::Type) //Обнаружили карту
                {
                    xmlWriter.writeTextElement("type", "Map");
                }

                //!
                //! делается
                //!
                
                    xmlWriter.writeTextElement("PosX", QString::number(item->pos().x()));
                    xmlWriter.writeTextElement("PosY", QString::number(item->pos().y()));
                
                // Add more properties as needed
                xmlWriter.writeEndElement(); // End Item
            }
        }

        xmlWriter.writeEndElement(); // End SceneItems
        xmlWriter.writeEndDocument();

        return xmlData;
    }


void Server::deserializeSceneFromXML(const QString &xmlData) { 
    QXmlStreamReader xml(xmlData);
    
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == "Item") {
            QString type;
            qreal posX = 0, posY = 0;

            // Read attributes or child elements
            while (xml.readNextStartElement()) {
                if (xml.name() == "type") {
                    type = xml.readElementText();
                } else if (xml.name() == "PosX") {
                    posX = xml.readElementText().toDouble();
                } else if (xml.name() == "PosY") {
                    posY = xml.readElementText().toDouble();
                } else {
                    xml.skipCurrentElement();
                }
            }
 
            foreach (QGraphicsItem *item, m_scene->items()) {
                if (!(item->pos().x() == 0 && item->pos().y() == 0)){
                    m_scene->removeItem(item);
                }
            }
            
            if (type != "Map")
            {
                Item* item;
                if (type == "Monster") {
                    item = new Item(Item::ItemType::Monster, m_scene->menu());
                } 
                else if (type == "Hero") {
                    item = new Item(Item::ItemType::Hero, m_scene->menu());
                } 
                else {   
                    item = new Item(Item::ItemType::Weapon, m_scene->menu());
                }

                item->setBrush(Qt::transparent);
                item->setPen(QPen(item->color(), 4));
                m_scene->addItem(item); //надо проверить название <3
                item->setPos(posX, posY);
                //emit itemInserted(item);

            } else if (type == "Map") {
                    MapItem* map = new MapItem(QPixmap(":/images/dungeon.png"), m_scene->menu());
                    map->setPos(posX, posY);
                    m_scene->addItem(map);
            }

            if (xml.hasError()) {
                qDebug() << "XML Error:" << xml.errorString();
            }
        }
    }
}
