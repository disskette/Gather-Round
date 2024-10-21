#include "tcpcli.h"

Client::Client(Scene *scene, QObject *parent)
        : QObject(parent), m_scene(scene), socket(new QTcpSocket(this))
    {

        connect(socket, &QTcpSocket::connected, this, &Client::sendInfo);
        connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
        //!
        QString ip = "";
        for (int i = 2; i <= 254; ++i) {
            //QString ip = QString("192.168.0.%1").arg(i);
            //ip = QString("10.110.124.%1").arg(i);
            ip = QString("192.168.0.%1").arg(i);
            
            qDebug() << "Проверка соединения с" << ip;
            
            socket->connectToHost(ip, 5702); 
            
            if (socket->waitForConnected(100)) {
                qDebug() << "Успешное соединение с" << ip;
                //socket->disconnectFromHost();
                break;
            } else {
                qDebug() << "Не удалось подключиться к" << ip << ":" << socket->errorString();

            }
        }

        //!
        //QString subnet = "10.110.124.18";
        //int port = 5702;

        qDebug() << "mi ne ochen w zope";

        //!socket->connectToHost(subnet, port);
        socket->connectToHost(ip, 5702); 

        qDebug() << "test connection?";
        sendInfo();
        qDebug() << "info sent?";

        /*QStringList parts = subnet.split('.');
        if (parts.size() != 4) {
            qDebug() << "Invalid subnet format. Use xxx.xxx.xxx.xxx";
            return;
        }

        qDebug() << "mi w ahue";

        for (int i = 1; i < 255; ++i) {
            QString ip = QString("%1.%2.%3.%4")
                            .arg(parts[0])
                            .arg(parts[1])
                            .arg(parts[2])
                            .arg(i);

            QHostAddress address(ip);
            QTcpSocket socket;

            qDebug() << "Trying to connect to" << address.toString() << "on port" << port;

            socket.connectToHost(address, port);

            if (socket.waitForConnected(1000)) { // Wait for connection with a timeout of 1 second
                qDebug() << "Connected to" << address.toString();
                socket.connectToHost(address, port);

            } else {
                qDebug() << "Failed to connect to" << address.toString();
            }
        }*/
        
        
    }


void Client::sendInfo()
    {
        qDebug() << "Connected to server.";
        // Send GET_ITEMS command
        socket->write("GET_ITEMS\n");
    }


void Client::onDisconnected()
    {
        qDebug() << "Disconnected from server.";
    }


void Client::deserializeSceneFromXML(const QString &xmlData) { 
    QXmlStreamReader xml(xmlData);
    
    foreach (QGraphicsItem *item, m_scene->items()) {
                if (!(item->pos().x() == 0 && item->pos().y() == 0)){
                    m_scene->removeItem(item);
                }
            }

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == "Item") {
            QString type;
            qreal posX = 0, posY = 0;

            // Read attributes or child elements
            while (xml.readNextStartElement()) {
                qDebug() << "XML name: "<<xml.name() ;
                if (xml.name() == "type") {
                    qDebug() << "In if";
                    type = xml.readElementText();
                } else if (xml.name() == "PosX") {
                    posX = xml.readElementText().toDouble();
                } else if (xml.name() == "PosY") {
                    posY = xml.readElementText().toDouble();
                } else {
                    xml.skipCurrentElement();
                }
            }
 

            qDebug() << type << "SUKAAAAAAAAAAAAAAAAAAAAAAAAAAAA";        
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
                    qDebug() << "Sosi zopu";
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

void Client::onReadyRead()
    {
        QByteArray responseData = socket->readAll();
        qDebug() << "Received data:" << responseData;

        // Parse XML data (assuming response is in XML format)
        deserializeSceneFromXML(responseData);
    }
