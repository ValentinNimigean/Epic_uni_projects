#include "Principal_window.h"
#include "Admin_window.h"
#include "User_window.h"
#include "Graph_window.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "BasketWindow.h"


MainWindow::MainWindow(Controller *service, QWidget *parent)
        : QMainWindow(parent), service(service){
    setupUi();
}


MainWindow::~MainWindow() {
    delete service;
}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *adminButton = new QPushButton("Administrator Mode", this);
    QPushButton *userButton = new QPushButton("User Mode", this);
    QPushButton *graphButton = new QPushButton("Graph Mode", this);

    layout->addWidget(adminButton);
    layout->addWidget(userButton);
    layout->addWidget(graphButton);


    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminMode);
    connect(userButton, &QPushButton::clicked, this, &MainWindow::onUserMode);
    connect(graphButton, &QPushButton::clicked, this, &MainWindow::onGraphMode);
    setCentralWidget(centralWidget);
}

void MainWindow::onAdminMode() {
    AdminWindow *adminWindow = new AdminWindow(service);
    adminWindow->resize(800, 600);
    adminWindow->show();

}

void MainWindow::onUserMode() {

    UserWindow *userWindow = new UserWindow(service);
    userWindow->show();


}
void MainWindow::onGraphMode() {
    BasketWindow *graphWindow = new BasketWindow(service->getBasket(), this);
    graphWindow->show();
}
