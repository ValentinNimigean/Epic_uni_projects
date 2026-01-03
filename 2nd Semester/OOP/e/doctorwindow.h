//
// Created by valen on 6/21/2024.
//

#ifndef OOP_E_911_915_915_NIMIGEAN_VALENTIN_DOCTORWINDOW_H
#define OOP_E_911_915_915_NIMIGEAN_VALENTIN_DOCTORWINDOW_H

#include <QWidget>
#include "Observer.h"
#include "Service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DoctorWindow; }
QT_END_NAMESPACE

class DoctorWindow : public QWidget ,public Observer{
Q_OBJECT

public:
    explicit DoctorWindow(Service* s,Doctor* d,QWidget *parent = nullptr);

    ~DoctorWindow() override;

private:
    Ui::DoctorWindow *ui;
    Service* cont;
    Doctor* doc;

    void update() override;
    void populate();

    void onCheck();

    void onAdd();

    void onElement();

    void onUpdate();
};


#endif //OOP_E_911_915_915_NIMIGEAN_VALENTIN_DOCTORWINDOW_H
