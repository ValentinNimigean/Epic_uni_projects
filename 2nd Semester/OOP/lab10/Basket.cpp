#include "Basket.h"

BasketModel::BasketModel(const std::vector<TrencchCoat>& basket, QObject* parent)
        : QAbstractTableModel(parent), basket(basket) {}

int BasketModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(basket.size());
}

int BasketModel::columnCount(const QModelIndex& ) const {
    return 5;
}

QVariant BasketModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const TrencchCoat& coat = basket.at(index.row());
    switch (index.column()) {
        case 0: return QString::fromStdString(coat.getSize());
        case 1: return QString::fromStdString(coat.getColor());
        case 2: return coat.getPrice();
        case 3: return coat.getQuantity();
        case 4: return QString::fromStdString(coat.getPhotograph());
        default: return QVariant();
    }
}

QVariant BasketModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Size";
            case 1: return "Color";
            case 2: return "Price";
            case 3: return "Quantity";
            case 4: return "Photo URL";
            default: return QVariant();
        }
    }
    return QVariant();
}
