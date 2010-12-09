// Master.cpp : main project file.

#include "stdafx.h"
#include <Formats.h>

using namespace System;
using namespace System::IO::Ports;

uint8_t buffer[RF12_MAXDATA];
RF12Message *msg;

int main(array<System::String ^> ^args)
{
    SerialPort port("COM8", 57600);
    port.Open();

    msg = reinterpret_cast<RF12Message *>(buffer);

    for(;;) {
      if(port.BytesToRead > 0) {
        buffer[0] = port.ReadByte();
        for(uint8_t i = 0; i < buffer[0]; ++i) {
          buffer[i] = port.ReadByte();
        }

        Console::WriteLine(L"MSG Type: {0}", msg->head.messageType);
      }
    }
}
