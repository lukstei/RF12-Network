#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NetworkManager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void connectTriggered();
    void connected(bool);

private:
    Ui::MainWindow *ui;
    NetworkManager *manager;
    
    QAction *connectAction;
};

#endif // MAINWINDOW_H
