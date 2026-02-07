//
// Created by valen on 4/3/2024.
//

#include "User_interface.h"
#include "Controller.h"
#include "Repository.h"
#include "Domain.h"
#include <iostream>
#include <string>
#include "Tests.h"
int main() {
    Repository repository;
    Controller controller(repository);
    User_interface user_interface(controller);
    Tests tests;
    tests.test_all();


    user_interface.run();


    return 0;
}