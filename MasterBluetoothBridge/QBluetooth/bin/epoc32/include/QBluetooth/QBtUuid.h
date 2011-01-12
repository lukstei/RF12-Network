#ifndef QBTUUID_H
#define QBTUUID_H

#include <QBtGlobal.h>
#include <QString>


/**
 * This class represents a UUID for Bluetooth, either in short format (16 or 32-bits) or full (128-bit).
 *
 */
class DLL_EXPORT QBtUuid
{
   public:

      /**
       * Constructs an empty instance.
       */
      QBtUuid ();


      /**
       * Constructs an instance from a string representation.
       *
       * Valid formats:
       * XXXX
       * XXXXXXXX
       * XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
       */
      QBtUuid (const QString & uuid);


      /**
       * Constructs an instance from a short uuid representation, a 16-bit or 32-bit value.
       */

      explicit QBtUuid (uint uuid);

   public:

      /**
       * Sets as short UUID based on the supplied value. Assumed to be a 16-bit or 32-bit hexadecimal number.
       */
      void set (uint uuid);

      /**
       * Sets the uuid from a string representation.
       *
       * Valid formats:
       * XXXX
       * XXXXXXXX
       * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
       * XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
       */
      void set (const QString & uuid);

      /**
       * If short uuid, returns the equivalent uint. If full uuid, returns 0.
       *
       */
      uint get() const;


      /**
       * If this is a full uuid, splits it four 32-bit values. If this is a short
       * uuid, all values are set to zero.
       *
       */
      void get (uint & highWord1, uint & highWord2, uint & lowWord1, uint & lowWord2) const;


      /**
       * If short format, returns the equivalent uint. If full uuid, returns 0.
       *
       */
      bool isFull () const;


      /**
       * Returns true if this is an empty instance.
       *
       */
      bool isNull () const;

      /**
       * Returns a string representation.
       *
       */
      QString toString() const;


      /**
       * Resets to a null UUID.
       */
      void clear();


      /**
       *
       */
      bool operator == (const QBtUuid & obj) const;


      /**
       *
       */
      bool operator != (const QBtUuid & obj) const;


   private:

      QString _uuid;


};



#ifdef Q_OS_SYMBIAN
#include <bttypes.h>

/**
 * A simple utility function to convert to the symbian native type.
 *
 */
inline TUUID QBtUuidToSymbianUuid (const QBtUuid & value)
{
   if (value.isFull() == false)
   {
      return TUUID (value.get() );
    }
    else
    {
      uint highWord1, highWord2, lowWord1, lowWord2;
      value.get (highWord1, highWord2, lowWord1, lowWord2);

      return TUUID (highWord1, highWord2, lowWord1, lowWord2);
    }
}

#endif

#endif // QBTUUID_H
