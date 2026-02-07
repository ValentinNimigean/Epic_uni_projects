//
// Created by valen on 4/3/2024.
//

#ifndef T1_915_NIMIGEAN_VALENTIN_1_USER_INTERFACE_H
#define T1_915_NIMIGEAN_VALENTIN_1_USER_INTERFACE_H

#include "Repository.h"
#include <iostream>
#include <string>
#include "Controller.h"

class User_interface {
private:
    Controller controller;
public:
    User_interface(Controller &controller);
    void run();


    void print_menu();
    ~User_interface();

};

#endif //T1_915_NIMIGEAN_VALENTIN_1_USER_INTERFACE_H
