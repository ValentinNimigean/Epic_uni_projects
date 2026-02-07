//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#include "Repository.h"

class Controller {
private:
    Repository repository;
    DynamicVector<TrencchCoat> shoppingBasket;
public:

    //default constructor
    Controller() ;


    //constructor with parameters
    Controller(Repository& repository);

    //removes a coat from the repository
    void removeCoat_Controller(const std::string& photograph);

    //updates a coat from the repository
    void updateCoat_Controller(const std::string& photograph, const std::string &size, const std::string &color, int price, int quantity);


    void addCoat_Controller(const std::string& size, const std::string& color, int price, int quantity, const std::string& photograph);

    int findCoat_Controller(const std::string& photo);

   DynamicVector<TrencchCoat> buildShoppingBasket(const std::string& size);

   void update_list_user_mode_controller(DynamicVector<TrencchCoat> list);


    DynamicVector<TrencchCoat> listCoats_Controller();




};

#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
