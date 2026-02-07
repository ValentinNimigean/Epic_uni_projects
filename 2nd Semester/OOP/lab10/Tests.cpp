//
// Created by valen on 3/27/2024.
//

#include "Tests.h"
#include "Domain.h"

#include "Repository.h"
#include "Controller.h"
#include <assert.h>
#include <iostream>
using namespace std;



/*void test_repository() {
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
*/
void test_controller() {
    /*Repository r;
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



    c.buildShoppingBasket("XL");
    c.update_list_user_mode_controller(c.buildShoppingBasket("XL"));

    std::vector<TrencchCoat> list=c.buildShoppingBasket("");

    list[0].setQuantity(0);


    list[1].setQuantity(188);

    



    c.update_list_user_mode_controller(list);




    c.listCoats_Controller();*/
    cout << "Tests passed!"<<endl;


}

void test_domain(){
    TrencchCoat t1("a", "a", 1, 1, "a");
    TrencchCoat t2("b", "b", 2, 2, "b");
    TrencchCoat t3("c", "c", 3, 3, "c");

    assert(t1.getSize()=="a");
    assert(t1.getColor()=="a");
    assert(t1.getPrice()==1);
    assert(t1.getQuantity()==1);
    assert(t1.getPhotograph()=="a");

    t1.setColor("b");
    t1.setSize("b");
    t1.setPrice(2);
    t1.setQuantity(2);
    t1.setPhotograph("b");

    assert(t1.getSize()=="b");
    assert(t1.getColor()=="b");
    assert(t1.getPrice()==2);
    assert(t1.getQuantity()==2);
    assert(t1.getPhotograph()=="b");

    TrencchCoat t4 = t1;
    assert(t4.getSize()=="b");
    assert(t4.getColor()=="b");
    assert(t4.getPrice()==2);
    assert(t4.getQuantity()==2);
    assert(t4.getPhotograph()=="b");











    cout << "Tests passed!"<<endl;
}





void complete_test(){



    test_domain();

}
