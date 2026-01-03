//
// Created by valen on 6/21/2024.
//

#ifndef OOP_E_911_915_915_NIMIGEAN_VALENTIN_DOCTOR_H
#define OOP_E_911_915_915_NIMIGEAN_VALENTIN_DOCTOR_H


#include <QString>

class Doctor{
private:
    QString name;
    QString specialisation;
public:
    Doctor(QString n, QString s):name(n),specialisation(s){};

    QString getName(){
        return name;
    }
    QString getSpecial(){
        return specialisation;
    }



};

#endif //OOP_E_911_915_915_NIMIGEAN_VALENTIN_DOCTOR_H
