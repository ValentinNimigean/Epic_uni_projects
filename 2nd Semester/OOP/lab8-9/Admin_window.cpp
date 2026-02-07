//
// Created by valen on 5/22/2024.
//

#include "Admin_window.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Domain.h"
#include<QShortcut>


AdminWindow::AdminWindow(Controller *service, QWidget *parent) : QWidget(parent), service(service) {
    setupUi();
}

AdminWindow::~AdminWindow() {
    delete service;
}



void AdminWindow::setupUi() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *addButton = new QPushButton("Add Trench Coat", this);
    QPushButton *deleteButton = new QPushButton("Delete Trench Coat", this);
    QPushButton *updateButton = new QPushButton("Update Trench Coat", this);
    QPushButton *viewButton = new QPushButton("View All Trench Coats", this);

   sizeEdit = new QLineEdit(this);
   colorEdit = new QLineEdit(this);
   priceEdit = new QLineEdit(this);
  quantityEdit = new QLineEdit(this);
  photoEdit = new QLineEdit(this);
    QLabel *sizeLabel = new QLabel("Size:", this);
    QLabel *colorLabel = new QLabel("Color:", this);
    QLabel *priceLabel = new QLabel("Price:", this);
    QLabel *quantityLabel = new QLabel("Quantity:", this);
    QLabel *photoLabel = new QLabel("Photo URL:", this);
    QPushButton *undoButton = new QPushButton("Undo", this);
    QPushButton *redoButton = new QPushButton("Redo", this);
    QShortcut *undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    QShortcut *redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);


    QHBoxLayout *undoRedoLayout = new QHBoxLayout();
    undoRedoLayout->addWidget(undoButton);
    undoRedoLayout->addWidget(redoButton);

    layout->addWidget(sizeLabel);
    layout->addWidget(sizeEdit);
    layout->addWidget(colorLabel);
    layout->addWidget(colorEdit);
    layout->addWidget(priceLabel);
    layout->addWidget(priceEdit);
    layout->addWidget(quantityLabel);
    layout->addWidget(quantityEdit);
    layout->addWidget(photoLabel);
    layout->addWidget(photoEdit);
    layout->addWidget(addButton);
    layout->addWidget(deleteButton);
    layout->addWidget(updateButton);
    layout->addWidget(viewButton);
    layout->addLayout(undoRedoLayout);





    connect(addButton, &QPushButton::clicked, this, &AdminWindow::onAdd);
    connect(deleteButton, &QPushButton::clicked, this, &AdminWindow::onDelete);
    connect(updateButton, &QPushButton::clicked, this, &AdminWindow::onUpdate);
    connect(viewButton, &QPushButton::clicked, this, &AdminWindow::onList);
    connect(undoButton, &QPushButton::clicked, this, &AdminWindow::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &AdminWindow::onRedo);
    connect(undoShortcut, &QShortcut::activated, this, &AdminWindow::onUndo);
    connect(redoShortcut, &QShortcut::activated, this, &AdminWindow::onRedo);
}

void AdminWindow::onAdd() {
   TrencchCoat coat;
    std::string size=sizeEdit->text().toStdString();
    std::string color=colorEdit->text().toStdString();
    int price=priceEdit->text().toInt();
    int quantity=quantityEdit->text().toInt();
    std::string photoUrl=photoEdit->text().toStdString();
    if(size.empty() || color.empty() || price == 0 || quantity == 0 || photoUrl.empty())
    {
        QMessageBox::information(this, "Info", "Invalid data.");
        return;
    }
    if(size!="XS" && size!="S" && size!="M" && size!="L" && size!="XL")
    {
        QMessageBox::information(this, "Info", "Invalid size.");
        return;
    }
    coat.setSize(size);
    coat.setColor(color);
    coat.setPrice(price);
    coat.setQuantity(quantity);
    coat.setPhotograph(photoUrl);
    if(service->findCoat_Controller(photoUrl)!=-1)
    {
        QMessageBox::information(this, "Info", "Coat already exists.");
        return;
    }
    service->addCoat_Controller(coat);
QMessageBox::information(this, "Info", "Coat added.");
}

void AdminWindow::onDelete() {
    // Gather photo URL from the user and delete the trench coat
    QString photoUrl = photoEdit->text();
    if (photoUrl.isEmpty()) {
        QMessageBox::information(this, "Info", "Invalid data.");
        return;
    }
    if(service->findCoat_Controller(photoUrl.toStdString())==-1)
    {
        QMessageBox::information(this, "Info", "Coat does not exist.");
        return;
    }
    service->removeCoat_Controller(photoUrl.toStdString());
    QMessageBox::information(this, "Info", "Coat deleted.");

}

void AdminWindow::onUpdate() {
    // Gather photo URL and new information from the user and update the trench coat
    QString photoUrl = photoEdit->text();
    if (photoUrl.isEmpty()) {
        QMessageBox::information(this, "Info", "Invalid data.");
        return;
    }
    if(service->findCoat_Controller(photoUrl.toStdString())==-1)
    {
        QMessageBox::information(this, "Info", "Coat does not exist.");
        return;
    }
    TrencchCoat coat;
    std::string size=sizeEdit->text().toStdString();
    std::string color=colorEdit->text().toStdString();
    int price=priceEdit->text().toInt();
    int quantity=quantityEdit->text().toInt();
    std::string photoUrl1=photoEdit->text().toStdString();
    if(size.empty() || color.empty() || price == 0 || quantity == 0 || photoUrl1.empty())
    {
        QMessageBox::information(this, "Info", "Invalid data.");
        return;
    }
    if(size!="XS" && size!="S" && size!="M" && size!="L" && size!="XL")
    {
        QMessageBox::information(this, "Info", "Invalid size.");
        return;
    }
    coat.setSize(size);
    coat.setColor(color);
    coat.setPrice(price);
    coat.setQuantity(quantity);
    coat.setPhotograph(photoUrl1);
    service->updateCoat_Controller(coat);
    QMessageBox::information(this, "Info", "Coat updated.");


}

void AdminWindow::onList() {
    // Display all trench coats
    std::vector<TrencchCoat> coats = service->listCoats_Controller();
    if (coats.empty()) {
        QMessageBox::information(this, "Info", "No trench coats available.");
        return;
    }

    sort(coats.begin(), coats.end(), [](const TrencchCoat &a, const TrencchCoat &b) {
        return a.getPrice() < b.getPrice();
    });
    sort(coats.begin(), coats.end(), [](const TrencchCoat &a, const TrencchCoat &b) {
        return a.getQuantity() < b.getQuantity();
    });

    std::string message;



    for (const auto& coat : coats) {
        message += coat.getSize() + " " + coat.getColor() + " " + std::to_string(coat.getPrice()) + " " + std::to_string(coat.getQuantity()) + " " + coat.getPhotograph() + "\n";
    }
    QMessageBox::information(this, "Trench Coats", QString::fromStdString(message));


}
void AdminWindow::onUndo() {
    // Undo the last operation
    std::string result = service->undo();
    QMessageBox::information(this, "Info", QString::fromStdString(result));
}

void AdminWindow::onRedo() {
    // Redo the last operation
    std::string result = service->redo();
    QMessageBox::information(this, "Info", QString::fromStdString(result));
}