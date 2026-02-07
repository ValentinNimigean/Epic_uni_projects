#include "Controller.h"
#include "Repository.h"
#include "Domain.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include "TrenchCoat_exceptions.h"
using namespace std;

Controller::Controller(Repository &repository, File_writer *file_writer) {
    this->repository = repository;
    this->file_writer = file_writer;



}


Controller::Controller() {
    this->repository = Repository();
    this->file_writer = new HTML_file();
}

void Controller::addCoat_Controller(TrencchCoat &coat) {
    RepositoryException::validate(repository,coat);
    this->repository.addCoat_repo(coat);
    undo_stack.push_back(Action{"add", coat});
    redo_stack.clear();
}

void Controller::removeCoat_Controller(const std::string &photograph) {
    RepositoryException::validate_remove(repository,photograph);
    this->repository.removeCoat_repo(photograph);

    undo_stack.push_back(Action{"remove", repository.getCoat(photograph)});
    redo_stack.clear();
}

void Controller::updateCoat_Controller(TrencchCoat &coat) {
    RepositoryException::validate_remove(repository,coat.getPhotograph());
    TrencchCoat old_coat = repository.getCoat(coat.getPhotograph());
    this->repository.updateCoat_repo(coat.getPhotograph(), coat);
    undo_stack.push_back(Action{"update", old_coat});
    redo_stack.clear();
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
    this->repository.saveToFile("repo.txt");
}

void Controller::save_basket_to_file(std::vector<TrencchCoat> list) {
    this->file_writer->save_to_file(std::move(list));
}

void Controller::open_basket() {
    this->file_writer->open_file();

}

vector<TrencchCoat> Controller::getTrenchCoatsBySize(string basicString) {
    vector<TrencchCoat> coats = this->repository.getCoats();
    vector<TrencchCoat> result;
    for (const auto &coat : coats) {
        if (coat.getSize() == basicString || basicString.empty()) {
            result.push_back(coat);
        }
    }
    return result;
}

Controller::~Controller() {
    delete this->file_writer;



}

Controller::Controller(File_writer *file_writer) {
    this->file_writer = file_writer;
    this->repository = Repository();

}

std::string Controller::undo() {
    if (undo_stack.empty()) {
        return "No more undos available.";
    }
    Action action = undo_stack.back();
    undo_stack.pop_back();
    if (action.action == "add") {
        repository.removeCoat_repo(action.coat.getPhotograph());
        redo_stack.push_back(action);
        return "Undo successful.";
    }
    if (action.action == "remove") {
        repository.addCoat_repo(action.coat);
        redo_stack.push_back(action);
        return "Undo successful.";
    }
    if (action.action == "update") {
        repository.updateCoat_repo(action.coat.getPhotograph(), action.coat);
        Action action1 = Action{"update", repository.getCoat(action.coat.getPhotograph())};
        redo_stack.push_back(action1);
        return "Undo successful.";
    }
return "Undo failed.";
}

std::string Controller::redo() {
    if (redo_stack.empty()) {
        return "No more redos available.";
    }
    Action action = redo_stack.back();
    redo_stack.pop_back();
    if (action.action == "add") {
        repository.addCoat_repo(action.coat);
        undo_stack.push_back(action);
        return "Redo successful.";
    }
    if (action.action == "remove") {
        repository.removeCoat_repo(action.coat.getPhotograph());
        undo_stack.push_back(action);
        return "Redo successful.";
    }
    if (action.action == "update") {
        repository.updateCoat_repo(action.coat.getPhotograph(), action.coat);
        undo_stack.push_back(action);
        return "Redo successful.";
    }
    return "Redo failed.";
}

void Controller::update_basket(TrencchCoat coat) {
    for(auto &coat1: this->basket){
        if(coat1.getPhotograph() == coat.getPhotograph()){
            coat1.setQuantity(coat1.getQuantity() + 1);
            return;
        }
    }
    coat.setQuantity(1);
    this->basket.push_back(coat);
}

std::vector<TrencchCoat> Controller::getBasket() {
    return this->basket;
}
