//
// Created by valen on 6/21/2024.
//

#ifndef OOP_E_911_915_915_NIMIGEAN_VALENTIN_PATIENT_H
#define OOP_E_911_915_915_NIMIGEAN_VALENTIN_PATIENT_H

#include <QString>
#include<ctime>

class Patient{
private:
    QString name;
    QString diagnosis;
    QString specialisation;
    QString doctor;
    int month;
    int year;
    int day;
public:
    Patient(QString n,QString d,QString s,QString doc,int m,int y, int d1):name(n),diagnosis(d),specialisation(s),doctor(doc),month(m),year(y),day(d1){};
    QString getSpecial(){
        return specialisation;
    }
    QString getName(){
        return  name;
    }
    QString getDoctor(){
        return doctor;
    };
    QString getDiagnosis(){
        return  diagnosis;
    }

    void setDiagnosis(QString qString) {
        diagnosis=qString;

    }

    void setSpecial(QString qString) {
        specialisation=qString;

    }
    void setDoctor(QString qString) {
        doctor=qString;

    }

    int getMonth(){
        return month;
    }
    int getYear(){
        return year;
    }
    int getDay(){
        return day;
    }
};

#endif //OOP_E_911_915_915_NIMIGEAN_VALENTIN_PATIENT_H
