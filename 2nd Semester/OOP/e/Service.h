//
// Created by valen on 6/21/2024.
//

#ifndef OOP_E_911_915_915_NIMIGEAN_VALENTIN_SERVICE_H
#define OOP_E_911_915_915_NIMIGEAN_VALENTIN_SERVICE_H
#include "Repository.h"
#include "Subject.h"

class Service:public Subject{
private:
    Repository* repo;
public:
    Service(Repository* r):repo(r){}
    QList<Doctor*> get_doctors(){
        return repo->get_docs();
    }

    QList<Patient*>get_patients(){
        return repo->get_pat();
    }

    QList<Patient*> get_good(Doctor* d){
        QList<Patient*> newList;
        for(Patient* p:repo->get_pat())
            if(p->getDoctor()==d->getName())
                newList.push_back(p);

        return newList;


    }
    void repoad(){
        repo->update();
    };
    void addPatient(Patient* p)
    {
        repo->addP(p);
        repo->update();


        notify();
    }





};

#endif //OOP_E_911_915_915_NIMIGEAN_VALENTIN_SERVICE_H
