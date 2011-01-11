#ifndef WEBAPP_H
#define WEBAPP_H

#include <QObject>
#include <QDateTime>
#include <QUrl>

#include <RF12Network/Network.h>
#include <RF12Network/Packet.h>

class WebApp : public QObject
{
  Q_OBJECT
  
public:
  explicit WebApp(QObject *parent = 0) :
      QObject(parent)
  {
  }
  
  virtual ~WebApp() {}

signals:
  void nodeCommand(MacAddress node, NodeCommand command);
    
public slots:
  virtual void sendValue(MacAddress node, int value, QDateTime time ) = 0;
};

#endif // WEBAPP_H
