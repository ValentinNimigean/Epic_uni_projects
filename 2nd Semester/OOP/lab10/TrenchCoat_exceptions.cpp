//
// Created by valen on 4/26/2024.
//

#include <cstring>
#include "TrenchCoat_exceptions.h"

ValidationInherited::ValidationInherited(std::string message) {
    this->message=message;

}

const char *ValidationInherited::what() const noexcept {
    return message.c_str();
}

void TrencchCoatvalidator::validate(const TrencchCoat &e) {

    string errors;
    if(e.getSize()!="XS" && e.getSize()!="S" && e.getSize()!="M"  && e.getSize()!="L" && e.getSize()!="XL"  && e.getSize()!="XXL")
    {
        errors+="INCORRECT SIZE \n";
    }
    if(e.getPrice()<=0)
    {
        errors+="INCORRECT PRICE \n";
    }
    if(e.getQuantity()<=0)
    {
        errors+="INCORRECT QUANTITY \n";
    }
    if (!errors.empty())
    {
        throw ValidationInherited(errors);
    }


}

void RepositoryException::validate(const Repository &r,const TrencchCoat &e) {
    for (auto & i :r.getCoats()) {
        if(i.getPhotograph()==e.getPhotograph())
        {
            throw ValidationInherited("COAT ALREADY EXISTS");
        }

    }

}

void RepositoryException::validate_remove(const Repository &r,const string &s)
{int k=0;
    for (auto &i : r.getCoats()){
        if (i.getPhotograph()==s)
            k=1;
    }
    if (k==0)
        throw ValidationInherited("COAT DOESNT EXIST");


}

