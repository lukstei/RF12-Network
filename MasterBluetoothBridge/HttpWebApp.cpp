#include "HttpWebApp.h"
#include "Helper.h"

HttpWebApp::HttpWebApp(QObject *parent) :
    WebApp(parent)
{
  QObject::connect(&net, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpFinished(QNetworkReply*)));
}

void HttpWebApp::sendValue(MacAddress node, int value, QDateTime time)
{
  QNetworkRequest req;
  req.setUrl(POST_URL);
  net.post(req, "data=" + QUrl::toPercentEncoding(getXml(node, value, time)));
}

void HttpWebApp::httpFinished(QNetworkReply *reply)
{

}

QString HttpWebApp::getXml(const MacAddress &node, int value, const QDateTime &time) const
{
  QByteArray arr;
  QXmlStreamWriter xml(&arr);
  xml.setAutoFormatting(true);
  xml.writeStartDocument();
  {
    xml.writeStartElement("rf12-values");
    {
      xml.writeTextElement("auth-token", AUTH_TOKEN);
      
      xml.writeStartElement("value");
      {
        xml.writeAttribute("node", Helper::getMacAddressString(node));
        xml.writeAttribute("type", "int");
        xml.writeAttribute("time", time.toString(Qt::ISODate));
        
        xml.writeCharacters(QString("%1").arg(value));
      }
      xml.writeEndElement();
    }
    xml.writeEndElement();
  }
  xml.writeEndDocument();
  
  return arr;
}
