#ifndef _BTDEVICEFINDER_DLG_SYMBIAN_H_
#define _BTDEVICEFINDER_DLG_SYMBIAN_H_
 
#include <e32base.h>
#include <BTExtNotifiers.h> //TBTDeviceSelectionParamsPckg,TBTDeviceResponseParamsPckg


class MBTDeviceFinderNotify
 {
 public:
		 virtual void BTDeviceSelectedL() = 0;
		 
		 virtual void BTCanceledL() = 0;
 };


// show a dialog and fills it with found devices
class CBTDeviceFinderDlg: public CActive
{

 public:
         static CBTDeviceFinderDlg* NewL (const TInt aPriority, MBTDeviceFinderNotify& aNotify);
         ~CBTDeviceFinderDlg();
 public:
		 void DiscoverDevicesL();
         void SetSelectionParams (const TBTDeviceSelectionParams& aFilter);
		 const TBTDeviceResponseParams& ResponseParams();

 protected:
		 void RunL();
		 void DoCancel();
 private:
         CBTDeviceFinderDlg (const TInt aPriority,MBTDeviceFinderNotify& aNotify);
		 void ConstructL(void);
 private:
	 RNotifier                     iSelectorNotifier;
	 MBTDeviceFinderNotify&        iNotify;                
	 TBTDeviceSelectionParamsPckg  iSelectParamsBuf;
	 TBTDeviceResponseParamsPckg   iResponseParamsBuf;
	 TBool                         iConnected;
 };




#endif
