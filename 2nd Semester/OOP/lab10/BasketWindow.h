//
// Created by valen on 6/4/2024.
//

#ifndef OOP_A8_9_915_NIMIGEAN_VALENTIN_BASKETWINDOW_H
#define OOP_A8_9_915_NIMIGEAN_VALENTIN_BASKETWINDOW_H

#include <QWidget>
#include <QTableView>
#include "Basket.h"

class BasketWindow : public QWidget {
Q_OBJECT

public:
    BasketWindow(const std::vector<TrencchCoat>& basket, QWidget* parent = nullptr);

private:
    QTableView* tableView;
    BasketModel* model;
};



#endif //OOP_A8_9_915_NIMIGEAN_VALENTIN_BASKETWINDOW_H
