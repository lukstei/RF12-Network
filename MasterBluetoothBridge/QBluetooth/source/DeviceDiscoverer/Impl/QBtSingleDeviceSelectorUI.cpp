#include "../QBtSingleDeviceSelectorUI.h"

#if defined(Q_OS_SYMBIAN)
#include "../QBtSingleDeviceSelectorUI_symbian.h"
#else
#include "../QBtSingleDeviceSelectorUI_stub.h"
#endif


//____________________________________________________________________________

QBtSingleDeviceSelectorUI::QBtSingleDeviceSelectorUI (QWidget* parent)
   : QObject (parent)
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING (_impl = QBtSingleDeviceSelectorUIPrivate::NewL(this));
#else
    _implPtr = new QBtSingleDeviceSelectorUIPrivate (parent, this);
#endif

}


//____________________________________________________________________________

QBtSingleDeviceSelectorUI::~QBtSingleDeviceSelectorUI()
{
   delete _impl;
}

//____________________________________________________________________________

void QBtSingleDeviceSelectorUI::show()
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING(_impl->ShowL() );
#else
    _impl->show();
#endif
}


