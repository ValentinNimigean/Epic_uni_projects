//
// Created by valen on 5/22/2024.
//

#ifndef OOP_A8_9_915_NIMIGEAN_VALENTIN_ADMIN_WINDOW_H
#define OOP_A8_9_915_NIMIGEAN_VALENTIN_ADMIN_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

#include "Controller.h"

class AdminWindow : public QWidget {
Q_OBJECT

public:
    AdminWindow(Controller *service, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void onAdd();
    void onDelete();
    void onUpdate();
    void onList();


private:
    void setupUi();

    Controller *service;
    QLineEdit *sizeEdit;
    QLineEdit *colorEdit;
    QLineEdit *priceEdit;
    QLineEdit *quantityEdit;
    QLineEdit *photoEdit;

    void onUndo();

    void onRedo();
};
#endif //OOP_A8_9_915_NIMIGEAN_VALENTIN_ADMIN_WINDOW_H
