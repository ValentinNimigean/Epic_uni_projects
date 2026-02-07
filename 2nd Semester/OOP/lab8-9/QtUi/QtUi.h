#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtUi.h"

class QtUi : public QMainWindow
{
    Q_OBJECT

public:
    QtUi(QWidget *parent = nullptr);
    ~QtUi();

private:
    Ui::QtUiClass ui;
};
