/*
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

#include <QBtSingleDeviceSelectorUIPrivate.h>
#include <QList>
#include <QBtAuxFunctions.h>
#include <QDesktopWidget>
#include <QApplication>

// ----------------------------------------------------------------------------
// QBtSingleDeviceSelectorUIPrivate::::QBtSingleDeviceSelectorUIPrivate(QWidget* parent) :
//		QFrame(parent), prnt(parent)
//
// constuctor
// ----------------------------------------------------------------------------
QBtSingleDeviceSelectorUIPrivate::QBtSingleDeviceSelectorUIPrivate (QWidget* parent, QBtSingleDeviceSelectorUI* publicClass) :
    QDialog(parent), _parent(parent), _selectedDevice(0), _discoverer(0),
    _devList(0), _menu(0), _select(0), _exit(0), _publicClass (publicClass)
{
    //setup UI
    setObjectName(QString::fromUtf8("btDeviceSelectorUIWidget"));
    setAutoFillBackground(true);
    //setFrameShape(QFrame::WinPanel);
    //setFrameShadow(QFrame::Sunken);
    this->setFocus();
    
    
    QDesktopWidget* dw = QApplication::desktop();
    int width = dw->screenGeometry().width();
    int height = dw->screenGeometry().height() /4;
        
    setGeometry(QRect(0, 148 , width, height));

    _verticalLayout = new QVBoxLayout(this);
    _verticalLayout->setSpacing(6);
    _verticalLayout->setMargin(11);
    _verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

    _label = new QLabel(this);
    _label->setText("Devices:");
    _verticalLayout->addWidget(_label);

    _devList = new QListWidget(this);

    /*QAction* clear = new QAction(tr("&Exit"), this);
    clear->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(clear, SIGNAL(triggered()), this, SLOT(closeWidget()));

    devList->addAction(clear);
    addAction(clear);*/

    _devList->setFocusPolicy(Qt::WheelFocus);
    _devList->setFrameShape(QFrame::WinPanel);
    _devList->setFrameShadow(QFrame::Sunken);
    _devList->setFocus();
    _verticalLayout->addWidget(_devList);

    _select = new QAction(QString("Select"), this);
    _select->setSoftKeyRole(QAction::PositiveSoftKey);
    connect(_select, SIGNAL(triggered()), this, SLOT(selectPressed()));
    addAction(_select);


    _exit = new QAction(QString("Cancel"), this);
    _exit->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(_exit, SIGNAL(triggered()), this, SLOT(exitPressed()));
    addAction(_exit);

    /*menu = new QMenuBar(this);
    menu->addAction(select);
    menu->addAction(exit);

    menu->setNativeMenuBar(true);
    verticalLayout->setMenuBar(menu);*/

    ////////////////

    _discoverer = new QBtDeviceDiscoverer(parent);

    connect(_discoverer, SIGNAL(newDeviceFound(const QBtDevice&)),
            this, SLOT(populateDeviceList(const QBtDevice&)));

    connect(_devList, SIGNAL(itemActivated(QListWidgetItem *)),
                    this, SLOT(devSelected(QListWidgetItem *)));
    this->hide();

}

// ----------------------------------------------------------------------------
// QBtSingleDeviceSelectorUIPrivate::~QBtSingleDeviceSelectorUIPrivate()
// destructor
// ----------------------------------------------------------------------------
QBtSingleDeviceSelectorUIPrivate::~QBtSingleDeviceSelectorUIPrivate()
{
    SafeDelete(_discoverer);
    //SafeDelete(selectedDevice);
    SafeDelete(_menu);
    SafeDelete(_select);
    SafeDelete(_exit);
}

// ----------------------------------------------------------------------------
// QBtSingleDeviceSelectorUIPrivate::show()
//
// On show, the device discovery starts an the UI is displayed
// ----------------------------------------------------------------------------
void QBtSingleDeviceSelectorUIPrivate::show()
{
    _devicesFound.clear();

    //menu->show();

    //int y1 = menu->geometry().top() - 150;
    //setGeometry(QRect(0, (y1 >= 0) ? y1 : 0 , 240, 150));
    QDialog::show();
    _devList->setFocus(Qt::PopupFocusReason);

    _discoverer->startDiscovery();
    emit _publicClass->discoveryStarted();
}


void QBtSingleDeviceSelectorUIPrivate::populateDeviceList(const QBtDevice& device)
{
    QBtDevice* newDev = new QBtDevice(device);
    _devicesFound.append(*newDev);
    _devList->addItem(device.getName());
}

void QBtSingleDeviceSelectorUIPrivate::devSelected(QListWidgetItem* devName)
{
    for(int i=0; i<_devicesFound.size(); i++)
    {
        if(_devicesFound[i].getName() == devName->text())
        {
            _selectedDevice = &(_devicesFound[i]);
            break;
        }
    }

    if(_selectedDevice)
        emit _publicClass->discoveryCompleted(*_selectedDevice);
    else
        emit _publicClass->discoveryCompleted(QBtDevice());


    this->hide();
    _parent->setFocusProxy(0);

    _discoverer->stopDiscovery();

    _devicesFound.clear();
    _devList->clear();
}

void QBtSingleDeviceSelectorUIPrivate::selectPressed()
{
    QList<QListWidgetItem*> selectedDevices = _devList->selectedItems();
    if(selectedDevices.size() > 0)
        devSelected(selectedDevices[0]);
}

void QBtSingleDeviceSelectorUIPrivate::exitPressed()
{
    this->hide();
    emit _publicClass->userCanceled();
}
