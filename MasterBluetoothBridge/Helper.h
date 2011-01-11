#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <RF12Network/Network.h>

class Helper : public QObject
{
  Q_OBJECT
private:
  explicit Helper(QObject *parent = 0);

public:
  static QString getMacAddressString(const MacAddress& address);
};

#endif // HELPER_H
