//
// Created by valen on 6/21/2024.
//

#include <QFile>
#include <QTextStream>
#include <iostream>
#include "Repository.h"
#include "Patient.h"

Repository::Repository() {

    QFile file("doctors.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream f(&file);
    while (!f.atEnd()){
        QString d=f.readLine();
        QStringList elements=d.split("^");
        Doctor* doc=new Doctor(elements[0],elements[1]);
        doctors.push_back(doc);


    }
    file.close();

    QFile file1("patients.txt");
    file1.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream f1(&file1);
    while (!f1.atEnd()){
        QString d=f1.readLine();
        QStringList elements=d.split("^");
        if(elements.size()==7){
            Patient* pat=new Patient(elements[0],elements[1],elements[2],elements[3],elements[4].toInt(),elements[5].toInt(),elements[6].toInt());
            patients.push_back(pat);
        }
        else{
            Patient* pat=new Patient(elements[0],"undiagnosed","","",elements[1].toInt(),elements[2].toInt(),elements[3].toInt());
            patients.push_back(pat);
        }



    }
    //std::sort(patients.begin(),patients.end(),[](Patient* a,Patient* b){return a->getName()<b->getName();});
    file1.close();




}
