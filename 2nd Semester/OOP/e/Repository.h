//
// Created by valen on 6/21/2024.
//

#ifndef OOP_E_911_915_915_NIMIGEAN_VALENTIN_REPOSITORY_H
#define OOP_E_911_915_915_NIMIGEAN_VALENTIN_REPOSITORY_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include "Doctor.h"
#include "Patient.h"
class Repository {
private:
    QList<Doctor *> doctors;
    QList<Patient *> patients;
public:
    Repository();

    QList<Doctor *> get_docs() {
        return this->doctors;
    }

    QList<Patient *> get_pat() {
        return this->patients;
    }

    void addP(Patient *p) {
        patients.push_back(p);


    }


    ~Repository() {
        QFile file("patients.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream f(&file);
        for (auto p: patients) {
            f << p->getName() << "^" << p->getDiagnosis() << "^" << p->getSpecial() << "^" << p->getDoctor() << "^"
              << p->getMonth() << "^" << p->getYear() << "^" << p->getDay() << "\n";
        }
    }


    void update() {
        QFile file("patients.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream f(&file);
        for (auto p: patients) {
            f << p->getName() << "^" << p->getDiagnosis() << "^" << p->getSpecial() << "^" << p->getDoctor() << "^"
              << p->getMonth() << "^" << p->getYear() << "^" << p->getDay() << "\n";
        }
    }
};
#endif //OOP_E_911_915_915_NIMIGEAN_VALENTIN_REPOSITORY_H
