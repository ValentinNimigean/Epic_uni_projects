//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_REPOSITORY_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_REPOSITORY_H

#include <string>

#include "Domain.h"
#include<vector>
using namespace std;
class Repository {
private:
    std::vector<TrencchCoat> coats;
public:
    //default constructor
    Repository();

    //constructor with parameters

    //destructor



    //adds a coat to the repository
    void addCoat_repo(const TrencchCoat& e);

    //removes a coat from the repository
    void removeCoat_repo(const std::string& photo);

    void updateCoat_repo(const std::string& photo, const TrencchCoat& new_coat);
    //finds a coat in the repository
    int findCoat_repo(const std::string& photo);
    //returns the dynamic vector
    std::vector<TrencchCoat> getCoats() const { return coats; }



    //returns the size of the dynamic vector



    void readFromFile(const string &filename);

    void saveToFile(const string &filename);
};
#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_REPOSITORY_H
