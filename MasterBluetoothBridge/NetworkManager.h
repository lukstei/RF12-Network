#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = 0);

    bool isConnected() { return _connected; }
    
signals:
    void connected(bool connected);

public slots:
    void connect();
    void disconnect();
    
private:
    bool _connected;
};

#endif // NETWORKMANAGER_H
