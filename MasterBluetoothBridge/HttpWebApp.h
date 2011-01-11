#ifndef HTTPWEBAPP_H
#define HTTPWEBAPP_H

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtXml/QXmlStreamWriter>
#include "WebApp.h"

#define WEBAPP_URL  QUrl("http://localhost/")
#define POST_URL    QUrl(WEBAPP_URL.toString() + "input")
#define AUTH_TOKEN  QString("7fa31bc088a714b56633b9afda3a4c8e")

class HttpWebApp : public WebApp
{
  Q_OBJECT
  
public:
  explicit HttpWebApp(QObject *parent = 0);

signals:

public slots:
  virtual void sendValue(MacAddress node, int value, QDateTime time );
  
protected slots:
  void httpFinished(QNetworkReply *reply);
  
protected:
  QString getXml(const MacAddress &node, int value, const QDateTime &time) const;
  QNetworkAccessManager net;
};

#endif // HTTPWEBAPP_H
