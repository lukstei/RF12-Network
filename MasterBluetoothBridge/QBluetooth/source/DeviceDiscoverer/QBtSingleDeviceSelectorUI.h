/*
 * QBtSingleDeviceSelectorUI.h
 *
 *
 *      Author: ftylitak
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

#ifndef QBTSINGLEDEVICESELECTORUI_H_
#define QBTSINGLEDEVICESELECTORUI_H_

#include <QObject>
#include <QWidget>
#include <QBtGlobal.h>
#include <QBtDevice.h>

class QBtSingleDeviceSelectorUIPrivate;

/**
 * This class provides UI for searching remote bluetooth
 * devices, displaying them and selecting one device.
 *
 * When a device is selected, the UI is closed and the
 * device instance is returned through discoveryCompleted()
 * signal.
 * (NOTE: when closed it is not destroyed, just hiden)
 *
 * To use, create an instance of the class and call
 * show(). When shown, discovery starts as well.
 *
 * To get the selected remote device, the discoveryCompleted()
 * signal must be handled.
 */
class DLL_EXPORT QBtSingleDeviceSelectorUI : public QObject
{
    Q_OBJECT

public:
    /**
     * If parent == 0, the list will be showed as an independent
     * widget on the screen, thus it's not necessary for the client application
     * to have a GUI interface.
     *
     * For Symbian, it uses the native bluetooth search dialog. In this case, the "parent"
     * parameter has no effect.
     */
    QBtSingleDeviceSelectorUI (QWidget* parent = 0);

    /**
     * Destructor.
     */
    ~QBtSingleDeviceSelectorUI();


public slots:

    /**
     * On show, the device discovery starts.
     */
    void show();


signals:
    /**
     * Emitted after device discovery stops and user selects the desired device.     
     */
    void discoveryCompleted (const QBtDevice & selectedDevice);


    /**
     * Emitted after calling show() if and only if the device discovery starts successfully
     */
    void discoveryStarted();

    
    /**
     * Emitted when the user closes the UI without choosing any device.
     */
    void userCanceled ();    


private:
    QBtSingleDeviceSelectorUIPrivate* _impl;
    friend class QBtSingleDeviceSelectorUIPrivate;

};

#endif /* QBTSINGLEDEVICESELECTORUI_H_ */
