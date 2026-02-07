//
// Created by valen on 5/22/2024.
//

#ifndef OOP_A8_9_915_NIMIGEAN_VALENTIN_GRAPH_WINDOW_H
#define OOP_A8_9_915_NIMIGEAN_VALENTIN_GRAPH_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QFormLayout>
#include "Controller.h"


class Size_Chart: public QWidget {
Q_OBJECT

public:
    explicit Size_Chart(QWidget *parent = nullptr);

    void populate(const std::vector<TrencchCoat> &coats);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, int> sizes;

};




#endif //OOP_A8_9_915_NIMIGEAN_VALENTIN_GRAPH_WINDOW_H
