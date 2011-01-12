#include <btdevice.h> //TBTDeviceClass, TBTDeviceName
#include <bttypes.h> //TBTDevAddr

#include "../QBtSingleDeviceSelectorUI.h"
#include "../QBtSingleDeviceSelectorUI_symbian.h"


#include <QtCore>


QBtSingleDeviceSelectorUIPrivate::QBtSingleDeviceSelectorUIPrivate (QBtSingleDeviceSelectorUI* publicClass)
 : _finder (0), _publicClass (publicClass)
{}


QBtSingleDeviceSelectorUIPrivate::~QBtSingleDeviceSelectorUIPrivate()
{
   Cancel();
   delete _finder;
}

QBtSingleDeviceSelectorUIPrivate* QBtSingleDeviceSelectorUIPrivate::NewL (QBtSingleDeviceSelectorUI* publicClass)
{
    QBtSingleDeviceSelectorUIPrivate* self = new (ELeave) QBtSingleDeviceSelectorUIPrivate (publicClass);
	
	CleanupStack::PushL(self);
		self->ConstructL();
	CleanupStack::Pop();

	return self;
}


void QBtSingleDeviceSelectorUIPrivate::ConstructL()
{
    //CActive::TPriority priority (CActive::EPriorityUserInput);
    //_finder = CBTDeviceFinderDlg::NewL(priority, *this);
}
 

void QBtSingleDeviceSelectorUIPrivate::Cancel()
{
   if (_finder)
   {
      if (_finder->IsActive() )
         _finder->Cancel();
   }

}

void QBtSingleDeviceSelectorUIPrivate::ShowL()
{
    // cancel and delete previous instance
    Cancel();
    delete _finder;

    // new man
    CActive::TPriority priority (CActive::EPriorityUserInput);
    _finder = CBTDeviceFinderDlg::NewL(priority, *this);


    // here we go
    QT_TRYCATCH_LEAVING (emit _publicClass->discoveryStarted() );
    SelectDeviceL ();
}


void QBtSingleDeviceSelectorUIPrivate::SelectDeviceL ()
{

  /* search only within a specific subset of devices
  TBTDeviceSelectionParams selectionFilter;
  TBTDeviceClass deviceFilter(EMajorServiceObjectTransfer, EMajorDevicePhone,
        EMinorDevicePhoneUnclassified |
         EMinorDevicePhoneCellular |
        EMinorDevicePhoneCordless |
         EMinorDevicePhoneSmartPhone |
         EMinorDevicePhoneWiredModem |
        EMinorDevicePhoneCommonISDNAccess );

  selectionFilter.SetDeviceClass(deviceFilter);
  iFinder->SetSelectionParams(selectionFilter);
  */

    _finder->DiscoverDevicesL();

}
 
void QBtSingleDeviceSelectorUIPrivate::BTDeviceSelectedL()
{
	//Do something when BT device is selected
	//e.g. get details of the device the user selected    
  
	TBTDeviceResponseParams response = _finder->ResponseParams();  
	TBTDevAddr deviceAddress = response.BDAddr();
	TBTDeviceName deviceName = response.DeviceName();
	TBTDeviceClass deviceClass = response.DeviceClass();
	
	
	// on to qt types
	QBtAddress address (deviceAddress);
	
	// name
	QString name = QString::fromUtf16 (deviceName.Ptr(), deviceName.Length());
	
	// major device class
	QBtDevice::DeviceMajor majorClass;
	
	switch (deviceClass.MajorDeviceClass() )
	{
		case 0x00: //computer
			majorClass = QBtDevice::Miscellaneous;
			break;	     
		case 0x01:
			majorClass = QBtDevice::Computer;
			break;	
		case 0x02:
			majorClass = QBtDevice::Phone;
			break;
		case 0x03:
			majorClass = QBtDevice::LANAccess;
			break;   	
		case 0x04:
			majorClass = QBtDevice::AudioVideo;
			break;         	
		case 0x05:
			majorClass = QBtDevice::Peripheral;
			break;     
		case 0x06:
			majorClass = QBtDevice::Imaging;
			break;   
		default:
			majorClass = QBtDevice::Uncategorized;
			break;
	}
	
	// create device
	QBtDevice remoteDevice (name, address, majorClass);
	
	// if this throws, generate a leave as this is symbian code
	QT_TRYCATCH_LEAVING (emit _publicClass->discoveryCompleted (remoteDevice) );
		
}


void QBtSingleDeviceSelectorUIPrivate::BTCanceledL()
{
	// if this throws, generate a leave as this is symbian code
	QT_TRYCATCH_LEAVING  (emit _publicClass->userCanceled() );
}

