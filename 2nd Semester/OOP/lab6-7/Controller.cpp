#include "Controller.h"
#include "Repository.h"
#include "Domain.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include "TrenchCoat_exceptions.h"
using namespace std;

Controller::Controller( Repository&repository, File_writer *file_writer ) {
    this->repository = repository;
    this->file_writer = file_writer;
}


Controller::Controller() {
    this->repository = Repository();
    this->file_writer = nullptr;
}

void Controller::addCoat_Controller(TrencchCoat &coat) {
    RepositoryException::validate(repository,coat);
    this->repository.addCoat_repo(coat);
}

void Controller::removeCoat_Controller(const std::string &photograph) {
    RepositoryException::validate_remove(repository,photograph);
    this->repository.removeCoat_repo(photograph);
}

void Controller::updateCoat_Controller(TrencchCoat &coat) {
    RepositoryException::validate_remove(repository,coat.getPhotograph());
    this->repository.updateCoat_repo(coat.getPhotograph(), coat);
}

int Controller::findCoat_Controller(const std::string &photo) {
    return this->repository.findCoat_repo(photo);
}


std::vector<TrencchCoat> Controller::listCoats_Controller() {
    return this->repository.getCoats();
}

void Controller::update_list_user_mode_controller(std::vector<TrencchCoat> list) {

    for (auto &coat: list) {
        if (coat.getQuantity() == 0) {
            this->repository.removeCoat_repo(coat.getPhotograph());
        } else {
            this->repository.updateCoat_repo(coat.getPhotograph(), coat);
        }
    }

}

void Controller::save_basket_to_file(std::vector<TrencchCoat> list) {
    this->file_writer->save_to_file(std::move(list));
}

void Controller::open_basket() {
    this->file_writer->open_file();

}


