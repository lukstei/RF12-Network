#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QMap>
#include <QIODevice>

#include <RF12Network/Network.h>
#include <RF12Network/Packet.h>


class NetworkManager : public QObject
{
    Q_OBJECT
  
public:
    explicit NetworkManager(QIODevice *stream, QObject *parent = 0);

    virtual bool isConnected() const = 0;
    
public slots:
    virtual void disconnect();
    virtual void connect();
    virtual void nodeCommand(node_id node, NodeCommand command) = 0;
    
    virtual void onDeviceAdded(node_id node, MacAddress address);
    virtual void onDeviceRemoved(node_id node);
    
signals:
    void deviceAdded(node_id node, MacAddress address);
    void deviceRemoved(node_id node);
    
    void valueReceived(node_id id, int value);
    
    void connected(bool connected);
      
  protected:    
    QMap<node_id, MacAddress> table;
    QIODevice *serial;
};

#endif // NETWORKMANAGER_H
