//
// Created by valen on 6/4/2024.
//

#ifndef OOP_A8_9_915_NIMIGEAN_VALENTIN_BASKET_H
#define OOP_A8_9_915_NIMIGEAN_VALENTIN_BASKET_H
#include <QAbstractTableModel>
#include <vector>
#include <string>
#include "Controller.h"

class BasketModel : public QAbstractTableModel {
Q_OBJECT

public:
    BasketModel(const std::vector<TrencchCoat>& basket, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<TrencchCoat> basket;
};

#endif //OOP_A8_9_915_NIMIGEAN_VALENTIN_BASKET_H
