uid3 = 0x2003328D

INCLUDEPATH += $$EPOCROOT\epoc32\include

TEMPLATE = lib
TARGET   = QBluetooth_0x2003328D
DEFINES  += BLUETOOTH_LIB

QT += core

PUBLIC_HEADERS += QBtGlobal.h \
    QBtAuxFunctions.h \
	DeviceDiscoverer/QBtDeviceDiscoverer.h \
    BTTypes/QBtAddress.h \
    BTTypes/QBtDevice.h \
    BTTypes/QBtService.h \
    BTTypes/QBtConstants.h \
    BTTypes/QBtTypes.h \    
    BTTypes/QBtUuid.h \
    DeviceDiscoverer/QBtSingleDeviceSelectorUI.h \
    ServiceDiscoverer/QBtServiceDiscoverer.h \
    ServiceDiscoverer/QBtServiceDiscovererForAll.h \
    ServiceAdvertiser/QBtServiceAdvertiser.h \
    Connection/SerialPort/Server/QBtSerialPortServer.h \
    Connection/SerialPort/Client/QBtSerialPortClient.h \
    Connection/ObjectExchange/Client/QBtObjectExchangeClient.h \
    LocalDevice/QBtLocalDevice.h \
    Connection/ObjectExchange/Server/QBtObjectExchangeServer.h \
    QBluetooth.h

HEADERS += $$PUBLIC_HEADERS


SOURCES += Connection/ObjectExchange/Server/Impl/QBtObjectExchangeServer.cpp \
    LocalDevice/Impl/QBtLocalDevice.cpp \
    Connection/ObjectExchange/Client/Impl/QBtObjectExchangeClient.cpp \
    Connection/SerialPort/Client/Impl/QBtSerialPortClient.cpp \
    Connection/SerialPort/Server/Impl/QBtSerialPortServer.cpp \
    ServiceAdvertiser/Impl/QBtServiceAdvertiser.cpp \
    BTTypes/Impl/QBtService.cpp \
    ServiceDiscoverer/Impl/QBtServiceDiscoverer.cpp \
    ServiceDiscoverer/Impl/QBtServiceDiscovererForAll.cpp \
    DeviceDiscoverer/Impl/QBtSingleDeviceSelectorUI.cpp \
    DeviceDiscoverer/Impl/QBtDeviceDiscoverer.cpp \
    BTTypes/Impl/QBtAddress.cpp \
    BTTypes/Impl/QBtDevice.cpp \
    BTTypes/Impl/QBtUuid.cpp

FORMS += 

RESOURCES +=  

symbian { 
	# fix for Qt Creator to find the symbian headers
	INCLUDEPATH += $$EPOCROOT\epoc32\include

    deploy.path = $$EPOCROOT
    exportheaders.sources = $$PUBLIC_HEADERS
    exportheaders.path = epoc32/include

    INCLUDEPATH += $$deploy.path$$exportheaders.path/QBluetooth/

    INCLUDEPATH += $$deploy.path$$exportheaders.path


    TARGET.UID3 = 0x2003328D

    TARGET.EPOCALLOWDLLDATA = 1

    HEADERS += Connection/ObjectExchange/Server/QBtObjectExchangeServer_symbian.h \
        LocalDevice/QBtLocalDevice_symbian.h \
        Connection/ObjectExchange/Client/QBtObjectExchangeClient_symbian.h \
        Connection/SerialPort/Client/QBtSerialPortClient_symbian.h \
        Connection/SerialPort/Server/QBtSerialPortServer_symbian.h \
        ServiceAdvertiser/QBtServiceAdvertiser_symbian.h \
        ServiceDiscoverer/QBtServiceDiscoverer_symbian.h \
        DeviceDiscoverer/QBtDeviceDiscoverer_symbian.h \
        DeviceDiscoverer/QBtSingleDeviceSelectorUI_symbian.h \
        DeviceDiscoverer/BtDeviceFinderDlg_symbian.h

    SOURCES += Connection/ObjectExchange/Server/Impl/QBtObjectExchangeServer_symbian.cpp \
        LocalDevice/Impl/QBtLocalDevice_symbian.cpp \
        Connection/ObjectExchange/Client/Impl/QBtObjectExchangeClient_symbian.cpp \
        Connection/SerialPort/Client/Impl/QBtSerialPortClient_symbian.cpp \
        Connection/SerialPort/Server/Impl/QBtSerialPortServer_symbian.cpp \
        ServiceAdvertiser/Impl/QBtServiceAdvertiser_symbian.cpp \
        ServiceDiscoverer/Impl/QBtServiceDiscoverer_symbian.cpp \
        DeviceDiscoverer/Impl/QBtDeviceDiscoverer_symbian.cpp \
        DeviceDiscoverer/Impl/QBtSingleDeviceSelectorUI_symbian.cpp \
        DeviceDiscoverer/Impl/BtDeviceFinderDlg_symbian.cpp
    
    # more libs based on s60 version
    contains (S60_VERSION, 3.1):BT_PLUGIN_LIB = -lbteng
    else:BT_PLUGIN_LIB = -lbtengsettings
    
    #
    LIBS += -lbluetooth \
         -lbtextnotifiers \
        -lsdpdatabase \
        -lsdpagent \
        -lirobex \
        -lefsrv \
        -lfeatdiscovery \
        -lcentralrepository \
        -lbafl \
        -leikcore \
        -lcone \
        -lbtdevice \
        -lbtmanclient \
        -lesock \    	
    	-lapmime \
    	-lcommonui \
    	-lplatformenv \
    	-lcharconv
    	
    	
    LIBS += $$BT_PLUGIN_LIB
    
    TARGET.CAPABILITY = All -TCB -AllFiles -DRM
    
    for(header, exportheaders.sources):BLD_INF_RULES.prj_exports += "$$header $$deploy.path$$exportheaders.path/QBluetooth/$$basename(header)"
	
	# add this for Qt Creator to generate a pkg file, it seems to be a bug in the current version (2.0.0)
	addFiles.sources = QBluetooth_0x2003328D.dll
	addFiles.path = !:\sys\bin
	DEPLOYMENT += addFiles    
}


else { 
    win32 { 
        LIBS += -lBlueSoleil_SDK_2.0.5/bin/BsSDK
		
		//deploy.path = $$EPOCROOT
		/*INCLUDEPATH += $$deploy.path$$exportheaders.path/QBluetooth/
		INCLUDEPATH += $$deploy.path$$exportheaders.path*/
		
        INCLUDEPATH = ./ \
			BTTypes	\
			BlueSoleil_SDK_2.0.5/include \
            Connection/ObjectExchange/Server \
            LocalDevice \
            Connection/ObjectExchange/Client \
            Connection/SerialPort/Client \
            Connection/SerialPort/Server \
            ServiceAdvertiser \
            ServiceDiscoverer \
            DeviceDiscoverer \
            WinSerialPort
        DESTDIR += $$(QTDIR)\QBluetooth\bin
        HEADERS += Connection/ObjectExchange/Server/QBtObjectExchangeServer_win32.h \
            LocalDevice/QBtLocalDevice_win32.h \
            Connection/ObjectExchange/Client/QBtObjectExchangeClient_win32.h \
            Connection/SerialPort/Client/QBtSerialPortClient_win32.h \
            Connection/SerialPort/Server/QBtSerialPortServer_win32.h \
            ServiceAdvertiser/QBtServiceAdvertiser_win32.h \
            ServiceDiscoverer/QBtServiceDiscoverer_win32.h \
            DeviceDiscoverer/QBtDeviceDiscoverer_win32.h \
            WinSerialPort/Tserial_event.h
        SOURCES += Connection/ObjectExchange/Server/Impl/QBtObjectExchangeServer_win32.cpp \
            LocalDevice/Impl/QBtLocalDevice_win32.cpp \
            Connection/ObjectExchange/Client/Impl/QBtObjectExchangeClient_win32.cpp \
            Connection/SerialPort/Client/Impl/QBtSerialPortClient_win32.cpp \
            Connection/SerialPort/Server/Impl/QBtSerialPortServer_win32.cpp \
            ServiceAdvertiser/Impl/QBtServiceAdvertiser_win32.cpp \
            ServiceDiscoverer/Impl/QBtServiceDiscoverer_win32.cpp \
            DeviceDiscoverer/Impl/QBtDeviceDiscoverer_win32.cpp \
            WinSerialPort/Tserial_event.cpp
			

    }
    else { 
        HEADERS += Connection/ObjectExchange/Server/QBtObjectExchangeServer_stub.h \
            LocalDevice/QBtLocalDevice_stub.h \
            Connection/ObjectExchange/Client/QBtObjectExchangeClient_stub.h \
            Connection/SerialPort/Client/QBtSerialPortClient_stub.h \
            Connection/SerialPort/Server/QBtSerialPortServer_stub.h \
            ServiceAdvertiser/QBtServiceAdvertiser_stub.h \
            ServiceDiscoverer/QBtServiceDiscoverer_stub.h \
            DeviceDiscoverer/QBtDeviceDiscoverer_stub.h
        SOURCES += Connection/ObjectExchange/Server/Impl/QBtObjectExchangeServer_stub.cpp \
            LocalDevice/Impl/QBtLocalDevice_stub.cpp \
            Connection/ObjectExchange/Client/Impl/QBtObjectExchangeClient_stub.cpp \
            Connection/SerialPort/Client/Impl/QBtSerialPortClient_stub.cpp \
            Connection/SerialPort/Server/Impl/QBtSerialPortServer_stub.cpp \
            ServiceAdvertiser/Impl/QBtServiceAdvertiser_stub.cpp \
            ServiceDiscoverer/Impl/QBtServiceDiscoverer_stub.cpp \
            DeviceDiscoverer/Impl/QBtDeviceDiscoverer_stub.cpp
    }
}
