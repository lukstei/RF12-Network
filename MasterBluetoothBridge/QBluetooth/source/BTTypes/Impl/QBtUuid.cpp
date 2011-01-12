/*
 * QBtService.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../QBtUuid.h"
#include "../../QBtAuxFunctions.h"

#include <QStringList>


//____________________________________________________________________________
//
// Valid formats:
// XXXX
// XXXXXXXX
// XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX (TODO)

inline bool IsValidUuid (const QString & uuid)
{
   bool ok;

   switch (uuid.length() )
   {
      case 4:
      case 8:
      {
         uuid.toUInt (&ok, 16);
         return ok;
      }
      case 36:
      {

         // split
         QStringList list = uuid.split("-");

         if (list.length() != 5)
            return false;

         // check size
         if (list [0].length() != 8 ||
             list [1].length() != 4 ||
             list [2].length() != 4 ||
             list [3].length() != 4 ||
             list [4].length() != 12)
             return false;

         // check each part
         for (int i = 0; i < 5; ++i)
         {
            list[i].toUInt (&ok, 16);

            if (ok != true)
               return false;
         }

         // ok now
         return true;

      }

      case 32:
      {
         // split in four and check
         QStringList s;
         s.append(uuid.mid(0, 8));
         s.append(uuid.mid(8, 4));
         s.append(uuid.mid(16, 4));
         s.append(uuid.mid(24, 4));

         // check each part
         bool ok;
         for (int i = 0; i < s.length(); ++i)
         {
            s[i].toUInt (&ok, 16);

            if (ok != true)
               return false;
         }

         return true;

      } break;


      default:
         return false;
   }


}



//____________________________________________________________________________

inline QString UintToString (uint uuid)
{
   if (uuid <= 0xFFFF)
      return QString ("%1").arg (uuid, 4, 16, QLatin1Char('0') );
    else
      return QString ("%1").arg (uuid, 8, 16, QLatin1Char('0') );
}


//____________________________________________________________________________

QBtUuid::QBtUuid()
{
   _uuid.clear();
}


//____________________________________________________________________________
//
// uuid assumed as hexadecimal
//

QBtUuid::QBtUuid (uint uuid)
{
   set (uuid);
}


//____________________________________________________________________________
//
// uuid assumed to be in the following formats:
// XXXX
// XXXXXXXX
// XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
//

QBtUuid::QBtUuid (const QString & uuid)
{
   set (uuid);
}



//____________________________________________________________________________
//
// uuid assumed to be in hexadecimal, 16 or 32 bit.
//

void QBtUuid::set (uint uuid)
{
   set (UintToString(uuid) );
}

//____________________________________________________________________________
//
// Assumed to be short or full uuid.
//

void QBtUuid::set (const QString & value)
{
  // upper
  QString up = value.toUpper();

  // split
  QStringList list = up.split("-");

  // join all
  _uuid = list.join("");


  // checks
  BT_ASSERT_MSG2(IsValidUuid(_uuid), "invalid uuid", _uuid);
}


//____________________________________________________________________________
//
// If short uuid, returns the equivalent uint. If full uuid, returns 0.
//

uint QBtUuid::get() const
{
   if (isFull() )
      return 0;

   bool ok;
   return _uuid.toUInt (&ok, 16);
}


//____________________________________________________________________________
//
// If this is a full uuid, splits it four 32-bit values. If this is a short
// uuid, all values are set to zero.
//

void QBtUuid::get (uint & highWord1, uint & highWord2, uint & lowWord1, uint & lowWord2) const
{
  // split
   QStringList list = _uuid.split("-");

   // join all
   QString s = list.join("");

   // separate parts
   QString s1 = s.mid (0, 8);
   QString s2 = s.mid (8, 8);
   QString s3 = s.mid (16, 8);
   QString s4 = s.mid (24, 8);

   // convert
   bool ok;

   highWord1 = s1.toUInt(&ok, 16);
   highWord2 = s2.toUInt(&ok, 16);
   lowWord1  = s3.toUInt(&ok, 16);
   lowWord2  = s4.toUInt(&ok, 16);

}


//____________________________________________________________________________
//
// Returns the string representation
//

QString QBtUuid::toString () const
{  
  return _uuid;
}


//____________________________________________________________________________
//
// Checks if this is the full uuid
//

bool QBtUuid::isFull() const
{
   return _uuid.length() == 32;
}


//____________________________________________________________________________
//
//

bool QBtUuid::isNull () const
{
   return _uuid.length() == 0;
}

//____________________________________________________________________________

void QBtUuid::clear()
{
   _uuid.clear();
}

//____________________________________________________________________________

bool QBtUuid::operator == (const QBtUuid & obj) const
{ 
   return _uuid == obj._uuid;

}


//____________________________________________________________________________

bool QBtUuid::operator != (const QBtUuid & obj) const
{
   return _uuid != obj._uuid;
}
