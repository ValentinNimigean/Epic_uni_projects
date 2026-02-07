//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_REPOSITORY_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_REPOSITORY_H

#include <string>
#include "Dynamic_Vector.h"
#include "Domain.h"

class Repository {
private:
    DynamicVector<TrencchCoat> coats;
public:
    //default constructor
    Repository();

    //constructor with parameters


    //adds a coat to the repository
    void addCoat_repo(const TrencchCoat& e);

    //removes a coat from the repository
    void removeCoat_repo(const std::string& photo);

    void updateCoat_repo(const std::string& photo, const TrencchCoat& new_coat);
    //finds a coat in the repository
    int findCoat_repo(const std::string& photo);
    //returns the dynamic vector
    DynamicVector<TrencchCoat> getCoats() const { return coats; }


};
#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_REPOSITORY_H
