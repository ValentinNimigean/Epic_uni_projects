//
// Created by valen on 5/29/2024.
//

#ifndef OOP_T3_915_NIMIGEAN_VALENTIN_UI_H
#define OOP_T3_915_NIMIGEAN_VALENTIN_UI_H

#include <QMainWindow>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include "Service.h"
#include <QPushButton>
#include <iostream>

class MainWindow: public QMainWindow{
Q_OBJECT

private:
    QListWidget * sports;
QLineEdit*  filtering;
Service* service;
QLineEdit* descr;
QLineEdit* time;
QListWidget* new_list_1;
QLineEdit* hours;
QPushButton* button;
void fill_list(){
    QList<Exercise> sport= service->get_list();
    for(Exercise e:sport)
    {sports->addItem(e.toSTring());

    }

}

public:
    MainWindow(Service* service1,QMainWindow* parent= nullptr){
    service=service1;

    sports=new QListWidget(this);
    filtering=new QLineEdit(this);
    descr=new QLineEdit(this);
    time=new QLineEdit(this);
    button=new QPushButton("Show intervals and total time",this);
    new_list_1=new QListWidget(this);
    hours=new QLineEdit(this);


    QVBoxLayout* layout=new QVBoxLayout;
    layout->addWidget(filtering);


    layout->addWidget(sports);
    QHBoxLayout* fc3=new QHBoxLayout;
    fc3->addWidget(descr);
    fc3->addWidget(time);
    fc3->addWidget(button);
    layout->addLayout(fc3);
    layout->addWidget(new_list_1);
    layout->addWidget(hours);
    QWidget* centralWidget=new QWidget;
    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);
    fill_list();
        connect(filtering,&QLineEdit::textChanged,this,&MainWindow::filter);
        connect(button,&QPushButton::clicked,this,&MainWindow::intervals);



}

private slots:
    void filter(){

    QString number1=filtering->text();
    int number=number1.toInt();
    QList<Exercise> new_list=service->filter(number);
    sports->clear();
    for(Exercise e:new_list)
        sports->addItem(e.toSTring());
}
void intervals(){
    hours->setText("error");
    

}



};

#endif //OOP_T3_915_NIMIGEAN_VALENTIN_UI_H
