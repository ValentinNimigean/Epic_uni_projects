//
// Created by valen on 6/21/2024.
//

#ifndef OOP_E_911_915_915_NIMIGEAN_VALENTIN_SUBJECT_H
#define OOP_E_911_915_915_NIMIGEAN_VALENTIN_SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject{
private:
    std::vector<Observer*> observers;

public:
    void add_obs(Observer* o){
        observers.push_back(o);
    }
    void notify(){
        for(Observer* o:observers)
            o->update();
    }

};

#endif //OOP_E_911_915_915_NIMIGEAN_VALENTIN_SUBJECT_H
