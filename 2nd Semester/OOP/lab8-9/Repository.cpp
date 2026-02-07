#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Repository.h"
using namespace std;

Repository::Repository() {
    this->coats = std::vector<TrencchCoat>();
    this->readFromFile("repo.txt");
}

void Repository::addCoat_repo(const TrencchCoat& e) {
    this->coats.push_back(e);
    this->saveToFile("repo.txt");
}

void Repository::removeCoat_repo(const std::string& photo) {
    for (auto& coat : this->coats)
if (coat.getPhotograph() == photo) {
    this->coats.erase(std::remove(this->coats.begin(), this->coats.end(), coat), this->coats.end());
    break;
}

}

void Repository::updateCoat_repo(const std::string& photo, const TrencchCoat& new_coat) {
    for (auto &coat: this->coats) {
        if (coat.getPhotograph() == photo) {
            coat = new_coat;
            break; // No need to continue once the coat is found and updated
        }
    }
}

void Repository::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return;
    }

    TrencchCoat coat;
    while (file>>coat)
    {
        this->coats.push_back(coat);}
    file.close();


}

void Repository::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }
    for (const auto& coat : this->coats) {
        file << coat;
    }

    file.close();
}

int Repository::findCoat_repo(const std::string& photo) {
    int index = 0;
    for (const auto& coat : this->coats) {
        if (coat.getPhotograph() == photo) {
            return index;
        }
        ++index;
    }
    return -1;
}
TrencchCoat Repository::getCoat(std::string photo) {
    for (auto &coat: this->coats) {
        if (coat.getPhotograph() == photo) {
            return coat;
        }
    }
    return TrencchCoat{};
}

