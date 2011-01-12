#include "../BTDeviceFinderDlg_symbian.h"
 
CBTDeviceFinderDlg::CBTDeviceFinderDlg(const TInt aPriority, MBTDeviceFinderNotify& aNotify)
:CActive(aPriority),iNotify(aNotify),iConnected(EFalse)
{
}
 
CBTDeviceFinderDlg::~CBTDeviceFinderDlg()
{        
  Cancel();
  
  if (iConnected)
  {
    iSelectorNotifier.CancelNotifier (KDeviceSelectionNotifierUid);
    iSelectorNotifier.Close();
  }
  
}
 
CBTDeviceFinderDlg* CBTDeviceFinderDlg::NewL(const TInt aPriority, MBTDeviceFinderNotify& aNotify)
{
    CBTDeviceFinderDlg* self = new (ELeave) CBTDeviceFinderDlg(aPriority,aNotify);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
}
 
void CBTDeviceFinderDlg::ConstructL(void)
{
  CActiveScheduler::Add(this);
}
 
void CBTDeviceFinderDlg::DoCancel()
{
  iSelectorNotifier.CancelNotifier( KDeviceSelectionNotifierUid );
}
 
void CBTDeviceFinderDlg::RunL()
{	    
   // TODO: shut up leaves??

	
	// check if the user has selected some device
	switch (iStatus.Int() )
	{
		// user canceled
		case KErrCancel:
			iNotify.BTCanceledL();
			break;
			
		case KErrNone:
			iNotify.BTDeviceSelectedL();			
			break;
			
		// some error
		default: 
			User::Leave(iStatus.Int());
	}	
	
	// close notifier soon; if the callbacks leave, the resources were already fred
    //iSelectorNotifier.CancelNotifier (KDeviceSelectionNotifierUid);
    //iSelectorNotifier.Close();	
    
}

 
void CBTDeviceFinderDlg::DiscoverDevicesL()
{
  if (!iConnected)
  {
	  User::LeaveIfError(iSelectorNotifier.Connect());
      iConnected = ETrue;
  }  
 
  iSelectorNotifier.StartNotifierAndGetResponse(iStatus,
                  KDeviceSelectionNotifierUid, 
                  iSelectParamsBuf, 
                  iResponseParamsBuf);
  SetActive();
}
 
void CBTDeviceFinderDlg::SetSelectionParams(const TBTDeviceSelectionParams& aFilter)
{
  iSelectParamsBuf = aFilter;
}
 
const TBTDeviceResponseParams& CBTDeviceFinderDlg::ResponseParams()
{
  return iResponseParamsBuf();
}
