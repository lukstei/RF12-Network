#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    webApp(new HttpWebApp)//,
    //manager(new NetworkManager)
{
  ui->setupUi(this);
  
  connectAction = menuBar()->addAction("Connect", this, SLOT(connectTriggered()));
  
  //connect(manager, SIGNAL(connected(bool)), this, SLOT(connected(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::connected(bool connected)
{
  if(connected) {
    ui->statusLabel->setText(tr("Connected"));
  }
  else {
    ui->statusLabel->setText(tr("Not connected"));
  }
}

void MainWindow::connectTriggered()
{
  MacAddress node;
  node.Address[0] = 0xFF;
  node.Address[1] = 0x23;
  node.Address[2] = 0xF5;
  node.Address[3] = 0x1F;
  
  webApp->sendValue(node, 4543, QDateTime::currentDateTime());
  
  if(manager->isConnected()) {
    connectAction->setText(tr("&Connect"));
    manager->disconnect();
  }
  else {
    connectAction->setText(tr("&Disconnect"));
    manager->connect();
  }
}
