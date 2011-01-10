#ifndef RF12NETWORK_H
#define RF12NETWORK_H

class RF12Network : public QObject
{
  Q_OBJECT
  
public:
    RF12Network();

public slots:
    void connect();
    
signals:
    void deviceAdded();
};

#endif // RF12NETWORK_H
