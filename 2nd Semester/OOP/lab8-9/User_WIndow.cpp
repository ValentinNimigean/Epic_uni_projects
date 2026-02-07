#include "User_WIndow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>

#include "Graph_window.h"

UserWindow::UserWindow(Controller* service, QWidget *parent)
        : QWidget(parent), service(service), totalPrice(0), currentIndex(0) {
    setupUi();
}

UserWindow::~UserWindow() {}

void UserWindow::setupUi() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *viewButton = new QPushButton("View Trench Coats by Size", this);
    addToBasketButton = new QPushButton("Add to Basket", this);
    nextButton = new QPushButton("Next", this);
    previousButton = new QPushButton("Previous", this);
    QPushButton *viewBasketButton = new QPushButton("View Basket", this);
    chart = new Size_Chart(this);

    sizeLabel = new QLabel(this);
    colorLabel = new QLabel(this);
    priceLabel = new QLabel(this);
    quantityLabel = new QLabel(this);
    photoLabel = new QLabel(this);


    layout->addWidget(viewButton);
    layout->addWidget(sizeLabel);
    layout->addWidget(colorLabel);
    layout->addWidget(priceLabel);
    layout->addWidget(quantityLabel);
    layout->addWidget(photoLabel);
    layout->addWidget(addToBasketButton);
    layout->addWidget(nextButton);
    layout->addWidget(previousButton);
    layout->addWidget(viewBasketButton);
    layout->addWidget(chart);

    connect(viewButton, &QPushButton::clicked, this, &UserWindow::onViewTrenchCoatsBySize);
    connect(addToBasketButton, &QPushButton::clicked, this, &UserWindow::onAddToBasket);
    connect(nextButton, &QPushButton::clicked, this, &UserWindow::onNextCoat);
    connect(previousButton, &QPushButton::clicked, this, &UserWindow::onPreviousCoat);
    connect(viewBasketButton, &QPushButton::clicked, this, &UserWindow::onViewBasket);
    chart->populate(service->listCoats_Controller());
    chart->show();
}

void UserWindow::displayCurrentCoat() {
    if (displayedCoats.empty()) {
        sizeLabel->setText("Size: N/A");
        colorLabel->setText("Color: N/A");
        priceLabel->setText("Price: N/A");
        quantityLabel->setText("Quantity: N/A");
        photoLabel->clear();
        addToBasketButton->setEnabled(false);
        nextButton->setEnabled(false);
        previousButton->setEnabled(false);
    } else {
        const TrencchCoat &coat = displayedCoats[currentIndex];
        sizeLabel->setText("Size: " + QString::fromStdString(coat.getSize()));
        colorLabel->setText("Color: " + QString::fromStdString(coat.getColor()));
        priceLabel->setText("Price: " + QString::number(coat.getPrice()));
        quantityLabel->setText("Quantity: " + QString::number(coat.getQuantity()));
        QPixmap pixmap(QString::fromStdString(coat.getPhotograph()));
        photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));

        addToBasketButton->setEnabled(true);
        nextButton->setEnabled(true);
        previousButton->setEnabled(true);
    }
}

void UserWindow::onViewTrenchCoatsBySize() {
    QString size = QInputDialog::getText(this, "View Trench Coats", "Size (leave empty to view all):");
    displayedCoats = service->getTrenchCoatsBySize(size.toStdString());
    currentIndex = 0;
    displayCurrentCoat();
}

void UserWindow::onAddToBasket() {
    if (!displayedCoats.empty() && displayedCoats[currentIndex].getQuantity() > 0){
        basket.push_back(displayedCoats[currentIndex]);
        totalPrice += displayedCoats[currentIndex].getPrice();
        displayedCoats[currentIndex].setQuantity(displayedCoats[currentIndex].getQuantity() - 1);
        service->update_list_user_mode_controller(displayedCoats);
        service->update_basket(displayedCoats[currentIndex]);

        QMessageBox::information(this, "Basket", "Trench coat added to basket.");

        show_chart();
        update();
    }
}

void UserWindow::onNextCoat() {
    if (!displayedCoats.empty()) {
        currentIndex = (currentIndex + 1) % displayedCoats.size();
        displayCurrentCoat();
    }
}

void UserWindow::onPreviousCoat() {
    if (!displayedCoats.empty()) {
        currentIndex = (currentIndex - 1 + displayedCoats.size()) % displayedCoats.size();
        displayCurrentCoat();
    }
}

void UserWindow::onViewBasket() {
   service->save_basket_to_file(basket);
    service->open_basket();
    QMessageBox::information(this, "Basket", "Basket saved to file.");
}

void UserWindow::show_chart() {
    chart->populate(service->listCoats_Controller());
    chart->show();
}
