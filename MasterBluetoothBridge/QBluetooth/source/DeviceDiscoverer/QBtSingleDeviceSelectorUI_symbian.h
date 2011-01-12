#ifndef QBTDEVICEFINDER_PRIVATE_SYMBIAN_H_
#define QBTDEVICEFINDER_PRIVATE_SYMBIAN_H_
 

#include <QBtDevice.h>
#include "../BtDeviceFinderDlg_symbian.h"

class CBTDeviceFinderDlg;
class QBtSingleDeviceSelectorUI;

//____________________________________________________________________________

class QBtSingleDeviceSelectorUIPrivate : public CBase, MBTDeviceFinderNotify
{
	public:
		
        static QBtSingleDeviceSelectorUIPrivate* NewL (QBtSingleDeviceSelectorUI* publicClass);
		
		
	public:
		
        ~QBtSingleDeviceSelectorUIPrivate();
		
		
	// mirror public API

	public:
		
        void ShowL();
	
	public:


		//from MBTDeviceFinderNotify
		void BTDeviceSelectedL();
		void BTCanceledL();
		
		
	private:
		
        QBtSingleDeviceSelectorUIPrivate (QBtSingleDeviceSelectorUI* publicClass);
		void ConstructL ();
		
		void SelectDeviceL ();

        void Cancel();
	
	private:  
	
		
		//...
        CBTDeviceFinderDlg*         _finder;
        QBtSingleDeviceSelectorUI*  _publicClass;

};


#endif
