//
// Created by valen on 3/26/2024.
//
#include "Repository.h"
#include "Dynamic_Vector.h"

using namespace std;

Repository::Repository() {
    this->coats = DynamicVector<TrencchCoat>();
}

void Repository::addCoat_repo(const TrencchCoat& e) {
    this->coats.add(e);
}

void Repository::removeCoat_repo(const std::string& photo) {
    int i = 0;
    TrencchCoat removable;
    for (i = 0; i < this->coats.getSize(); i++)
        if (this->coats[i].getPhotograph() == photo)
            removable= this->coats[i];
    this->coats.remove(removable);
}


void Repository::updateCoat_repo(const std::string& photo, const TrencchCoat& new_coat) {
    int i = 0;
    for (i = 0; i < this->coats.getSize(); i++)
        if (this->coats[i].getPhotograph() == photo)
            this->coats.update(this->coats[i], new_coat);
}

int Repository::findCoat_repo(const std::string& photo) {
    for (int i = 0; i < this->coats.getSize(); i++)
        if (this->coats[i].getPhotograph() == photo)
            return i;
    return -1;
}




