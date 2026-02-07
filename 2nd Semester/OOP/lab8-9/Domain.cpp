//
// Created by valen on 3/26/2024.
//

#include "Domain.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;


TrencchCoat::TrencchCoat() {
    this->size = "";

    this->color = "";


    this->price = 0;
    this->quantity = 0;

    this->photograph = "";
}

TrencchCoat::TrencchCoat(const std::string& size, const std::string& color, int price, int quantity, const std::string& photograph) {
this->size = size;


    this->color = color;

    this->price = price;
    this->quantity = quantity;

    this->photograph = photograph;
}

TrencchCoat::TrencchCoat(const TrencchCoat& trencchCoat)
{

    this->price = trencchCoat.price;
    this->quantity = trencchCoat.quantity;

    this->size = trencchCoat.size;

    this->color = trencchCoat.color;

    this->photograph = trencchCoat.photograph;
}

TrencchCoat::~TrencchCoat() = default;



std::ostream& operator<<(std::ostream& os, const TrencchCoat& coat) {
    os << coat.size << "," << coat.color << "," << coat.price << "," << coat.quantity << "," << coat.photograph << "\n";
    return os;
}


vector<std::string> tokenize(const string& string, char delimiter) {
    vector<std::string> result;
    stringstream ss(string);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}



std::istream& operator>>(std::istream& is, TrencchCoat& coat) {
    std::string line;
    std::getline(is, line);
    std::vector<string> tokens=tokenize(line, ',');


    if (tokens.size() != 5)
        return is;
    else {
        coat.size = tokens[0];
        coat.color = tokens[1];
        coat.price = stoi(tokens[2]);
        coat.quantity = stoi(tokens[3]);
        coat.photograph = tokens[4];

    }
    return is;
}






bool TrencchCoat::operator==(const TrencchCoat& trencchCoat)
{
    return (this->photograph==trencchCoat.photograph) ;
}

TrencchCoat& TrencchCoat::operator=(const TrencchCoat& trencchCoat)
{
    if (this == &trencchCoat)
        return *this;

    this->price = trencchCoat.price;
    this->quantity = trencchCoat.quantity;

    this->size = trencchCoat.size;


    this->color = trencchCoat.color;


    this->photograph =trencchCoat.photograph;


    return *this;
}

std::string TrencchCoat::getPhotograph() const
{
    return this->photograph;
}

std::string TrencchCoat::getSize() const {
    return this->size;
}

std::string TrencchCoat::getColor() const {
    return this->color;
}

int TrencchCoat::getPrice() const {
    return this->price;
}

int TrencchCoat::getQuantity() const {
    return this->quantity;
}

void TrencchCoat::setSize(const std::string& size) {
    this->size = size;
}

void TrencchCoat::setColor(const std::string& color) {
    this->color = color;
}

void TrencchCoat::setPrice(int price) {
    this->price = price;
}

void TrencchCoat::setQuantity(int quantity) {
    this->quantity = quantity;
}

void TrencchCoat::setPhotograph(const std::string& photograph) {
    this->photograph = photograph;
}



