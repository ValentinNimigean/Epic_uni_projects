//
// Created by valen on 3/27/2024.
//
#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
#include "Controller.h"
class User_interface {
private:
    Controller controller;
public:
    User_interface(Controller &controller);
    ~User_interface();
    void run();
    int read_number();
    void addCoat_UI();
    void removeCoat_UI();
    void updateCoat_UI();
    void listCoats_UI();
    void printMenu();
    void user_mode();
    void admin_mode();
    void user_mode_basket();


};

#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
