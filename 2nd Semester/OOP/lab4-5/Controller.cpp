#include "Controller.h"
#include "Repository.h"
#include "Domain.h"
#include <cstring>
#include <iostream>
using namespace std;

Controller::Controller(Repository &repository) : repository(repository) {
    this->shoppingBasket = DynamicVector<TrencchCoat>();
}

Controller::Controller() {
    this->repository = Repository();

    this->shoppingBasket = DynamicVector<TrencchCoat>();
}
void Controller::addCoat_Controller(const std::string &size, const std::string &color, int price, int quantity, const std::string &photograph) {
    TrencchCoat coat(size, color, price, quantity, photograph);
    this->repository.addCoat_repo(coat);


}

void Controller::removeCoat_Controller(const std::string &photograph) {
    this->repository.removeCoat_repo(photograph);
}

void Controller::updateCoat_Controller(const std::string &photograph, const std::string &size, const std::string &color, int price, int quantity) {
    TrencchCoat coat(size, color, price, quantity, photograph);
    this->repository.updateCoat_repo(photograph, coat);
}

int Controller::findCoat_Controller(const std::string &photo) {
    return this->repository.findCoat_repo(photo);

}

DynamicVector<TrencchCoat> Controller::buildShoppingBasket(const std::string &size) {
    int i = 0;
    if (size == "")
    {
        for (i = 0; i < this->repository.getCoats().getSize(); i++)
            this->shoppingBasket.add(this->repository.getCoats()[i]);
        return this->shoppingBasket;
    } else
    {
        for (i = 0; i < this->repository.getCoats().getSize(); i++)
        if (this->repository.getCoats()[i].getSize() == size)
            this->shoppingBasket.add(this->repository.getCoats()[i]);
        return this->shoppingBasket;
    }
}

DynamicVector<TrencchCoat>Controller::listCoats_Controller() {
    return this->repository.getCoats();}

void Controller::update_list_user_mode_controller(DynamicVector<TrencchCoat> list) {

    this->shoppingBasket = list;
    for (int i = 0; i < this->shoppingBasket.getSize(); i++)

        if (this->shoppingBasket[i].getQuantity() == 0)
            this->repository.removeCoat_repo(this->shoppingBasket[i].getPhotograph());
        else
        this->repository.updateCoat_repo(this->shoppingBasket[i].getPhotograph(), this->shoppingBasket[i]);{

    }
    this->shoppingBasket = DynamicVector<TrencchCoat>();

}








