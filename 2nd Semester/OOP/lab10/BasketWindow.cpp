#include "BasketWindow.h"
#include <QVBoxLayout>

BasketWindow::BasketWindow(const std::vector<TrencchCoat>& basket, QWidget* parent)
        : QWidget(parent) {
    model = new BasketModel(basket, this);
    tableView = new QTableView(this);
    tableView->setModel(model);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    setLayout(layout);

    setWindowTitle("Shopping Basket");
    resize(600, 400);
}
