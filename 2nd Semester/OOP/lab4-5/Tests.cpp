//
// Created by valen on 3/27/2024.
//

#include "Tests.h"
#include "Domain.h"
#include "Dynamic_Vector.h"
#include "Repository.h"
#include "Controller.h"
#include <assert.h>
#include <iostream>
using namespace std;

void test_dynamic_vector() {
    DynamicVector <TrencchCoat>v(2);
    TrencchCoat t1("a", "a", 1, 1, "a");
    TrencchCoat t2("b", "b", 2, 2, "b");
    TrencchCoat t3("c", "c", 3, 3, "c");

    v.add(t1);
    v.add(t2);
    v.add(t3);
    cout << "Tests passed!"<<endl;
}

void test_repository() {
    Repository r;
    TrencchCoat t1("a", "a", 1, 1, "a");
    TrencchCoat t2("b", "b", 2, 2, "b");
    TrencchCoat t3("c", "c", 3, 3, "c");

    r.addCoat_repo(t1);
    r.addCoat_repo(t2);
    r.addCoat_repo(t3);

    assert(r.findCoat_repo("a") == 0);
    assert(r.findCoat_repo("b") == 1);
    assert(r.findCoat_repo("c") == 2);

    r.removeCoat_repo("a");
    r.removeCoat_repo("b");
    r.removeCoat_repo("c");

    assert(r.findCoat_repo("a") == -1);
    assert(r.findCoat_repo("b") == -1);
    assert(r.findCoat_repo("c") == -1);
    cout << "Tests passed!"<<endl;
}

void test_controller() {
    Repository r;
    Controller c(r);
    TrencchCoat t1("a", "a", 1, 1, "a");
    TrencchCoat t2("b", "b", 2, 2, "b");
    TrencchCoat t3("c", "c", 3, 3, "c");

    c.addCoat_Controller("a", "a", 1, 1, "a");
    c.addCoat_Controller("b", "b", 2, 2, "b");
    c.addCoat_Controller("c", "c", 3, 3, "c");

    assert(c.findCoat_Controller("a") == 0);
    assert(c.findCoat_Controller("b") == 1);
    assert(c.findCoat_Controller("c") == 2);

    c.removeCoat_Controller("a");
    assert(c.findCoat_Controller("a") == -1);

    c.updateCoat_Controller("b","xl", "b", 3, 3);

    cout << "Tests passed!"<<endl;


    c.buildShoppingBasket("XL");
    c.update_list_user_mode_controller(c.buildShoppingBasket("XL"));

    cout << "Tests passed!"<<endl;

}





void complete_test(){
    test_dynamic_vector();
    test_repository();
    test_controller();

}
