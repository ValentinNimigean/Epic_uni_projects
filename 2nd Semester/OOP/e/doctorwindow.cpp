//
// Created by valen on 6/21/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DoctorWindow.h" resolved

#include "doctorwindow.h"
#include "ui_DoctorWindow.h"
#include <QMessageBox>
#include <iostream>


DoctorWindow::DoctorWindow(Service*s,Doctor*d,QWidget *parent):cont(s),doc(d),
        QWidget(parent), ui(new Ui::DoctorWindow) {
    ui->setupUi(this);
    setWindowTitle(d->getName());
    connect(ui->spec,&QCheckBox::pressed,this,&DoctorWindow::onCheck);
    connect(ui->spec,&QCheckBox::released,this,&DoctorWindow::populate);
    connect(ui->pushButton,&QPushButton::clicked,this,&DoctorWindow::onAdd);
    connect(ui->patientslist,&QListWidget::itemClicked, this,&DoctorWindow::onElement);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&DoctorWindow::onUpdate);
    populate();

}

void DoctorWindow::update() {
    populate();
}

DoctorWindow::~DoctorWindow() {
    delete ui;
}

void DoctorWindow::populate() {
    ui->patientslist->clear();

    for(Patient* p:cont->get_patients()) {

        if (p->getSpecial() == doc->getSpecial() || p->getDiagnosis() == "undiagnosed") {
            QListWidgetItem *L = new QListWidgetItem(p->getName() + "," + p->getDiagnosis()+","+QString::number(p->getYear())+","   +QString::number(p->getMonth())+","   +QString::number(p->getDay()));

            if (p->getDoctor() == doc->getName()) {
                L->setBackground(QColor("green"));
            }
            ui->patientslist->addItem(L);
        }
    }



}


void DoctorWindow:: onCheck(){

    QList<Patient*> l=cont->get_good(doc);
    ui->patientslist->clear();
    for(Patient* p: l)
    {QListWidgetItem* x= new QListWidgetItem(p->getName() + "," + p->getDiagnosis()+","+QString::number(p->getYear())+","   +QString::number(p->getMonth())+","   +QString::number(p->getDay()));
        ui->patientslist->addItem(x);


    }
    ui->patientslist->setSortingEnabled(true);


};

void DoctorWindow::onAdd(){

    QString name=ui->lineEdit->text();
    if(name=="")
        QMessageBox ::warning(this,"Error","Name cannot be empty");
    else
    {
        QString date=ui->lineEdit_5->text();
        QStringList exact=date.split("/");
        if(exact[1].toInt()<2024)
            QMessageBox ::warning(this,"Error","In the past");
        else
        {
            QString diagnosis=ui->lineEdit_2->text();
            QString specialisation=ui->lineEdit_3->text();
            QString doctor=ui->lineEdit_4->text();
            if (diagnosis=="")
                diagnosis="undiagnosed";
            Patient* p=new Patient(name,diagnosis,specialisation,doctor,exact[0].toInt(),exact[1].toInt(),exact[2].toInt());
            cont->addPatient(p);
            populate();
        }




    }


    }

void DoctorWindow:: onElement(){

    QString a=ui->patientslist->currentItem()->text();
    QStringList elements=a.split(",");
    for(Patient* p: cont->get_patients())
        if(p->getName()==elements[0]) {
            ui->lineEdit_6->setText(p->getDiagnosis());
        ui ->lineEdit_7->setText(p->getSpecial());}



}

void DoctorWindow::onUpdate(){

    QString new_diag=ui->lineEdit_6->text();
    QString new_spec=ui->lineEdit_7->text();
    if(new_diag=="undiagnosed")
        QMessageBox ::warning(this,"Error","INVALID");
    else
    for(Patient* p: cont->get_patients())

        if(p->getName()==ui->patientslist->currentItem()->text().split(",")[0])
        {
            p->setDiagnosis(new_diag);
            p->setSpecial(new_spec);

            if (p->getSpecial()!=doc->getSpecial())
                for(Doctor* d: cont->get_doctors())
                    if(d->getSpecial()==p->getSpecial())
                    {p->setDoctor(d->getName());

                        cont->repoad();


                    }
        }

    cont->notify();



}