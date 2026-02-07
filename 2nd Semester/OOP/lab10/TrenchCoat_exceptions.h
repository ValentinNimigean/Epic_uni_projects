//
// Created by valen on 4/26/2024.
//

#ifndef OOP_A6_7_915_NIMIGEAN_VALENTIN_TRENCHCOAT_EXCEPTIONS_H
#define OOP_A6_7_915_NIMIGEAN_VALENTIN_TRENCHCOAT_EXCEPTIONS_H

#include <exception>
#include "Domain.h"
#include <string>
#include "Repository.h"
class ValidationInherited: public std::exception
{
private:
    std::string message;

public:
    ValidationInherited(std::string message);
    const char* what() const noexcept override;

};


class TrencchCoatvalidator{
public:
    static void validate(const TrencchCoat& e);
};


class RepositoryException: public std::exception
{
public:
    static void validate(const Repository &r,const TrencchCoat& e);



    static void validate_remove(const Repository &r, const string &s);
};
#endif //OOP_A6_7_915_NIMIGEAN_VALENTIN_TRENCHCOAT_EXCEPTIONS_H
