//
// Created by valen on 3/26/2024.
//
#include "Domain.h"
#include <iostream>
#include <cstring>
#include "Dynamic_Vector.h"
#include "Repository.h"
#include "Controller.h"
#include "User_interface.h"
#include "Tests.h"
int main(){
    Repository repository;
    Controller controller{repository};
    User_interface user_interface{controller};
    complete_test();
    user_interface.hard_Coded();
    user_interface.run();








    return 0;
}