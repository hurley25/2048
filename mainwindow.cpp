#include "mainwindow.h"

#include "gamecontrol.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *widget = new GameControl();
    this->setCentralWidget(widget);
    this->setFixedSize(widget->size());
    this->setWindowTitle("2048");
}
