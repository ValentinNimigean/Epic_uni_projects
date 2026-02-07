//
// Created by valen on 3/26/2024.
//

#include "Domain.h"
#include <iostream>
#include <cstring>



TrencchCoat::TrencchCoat() {
    this->size = new char[1];
    strcpy_s(this->size, 1, "");

    this->color = new char[1];
    strcpy_s(this->color, 1, "");

    this->price = 0;
    this->quantity = 0;

    this->photograph = new char[1];
    strcpy_s(this->photograph, 1, "");
}

TrencchCoat::TrencchCoat(const std::string& size, const std::string& color, int price, int quantity, const std::string& photograph) {
this->size = new char[size.length() + 1];
    strcpy_s(this->size, size.length() + 1, size.c_str());

    this->color = new char[color.length() + 1];
    strcpy_s(this->color, color.length() + 1, color.c_str());

    this->price = price;
    this->quantity = quantity;

    this->photograph = new char[photograph.length() + 1];
    strcpy_s(this->photograph, photograph.length() + 1, photograph.c_str());
}

TrencchCoat::TrencchCoat(const TrencchCoat& trencchCoat)
{

    this->price = trencchCoat.price;
    this->quantity = trencchCoat.quantity;

    this->size = new char[strlen(trencchCoat.size) + 1];
    strcpy_s(this->size, strlen(trencchCoat.size) + 1, trencchCoat.size);

    this->color = new char[strlen(trencchCoat.color) + 1];
    strcpy_s(this->color, strlen(trencchCoat.color) + 1, trencchCoat.color);

    this->photograph = new char[strlen(trencchCoat.photograph) + 1];
    strcpy_s(this->photograph, strlen(trencchCoat.photograph) + 1, trencchCoat.photograph);
}


TrencchCoat::~TrencchCoat()
{
    delete[] this->size;
    delete[] this->color;
    delete[] this->photograph;

}

bool TrencchCoat::operator==(const TrencchCoat& trencchCoat)
{
    return strcmp(this->photograph, trencchCoat.photograph) == 0;
}

TrencchCoat& TrencchCoat::operator=(const TrencchCoat& trencchCoat)
{
    if (this == &trencchCoat)
        return *this;

    this->price = trencchCoat.price;
    this->quantity = trencchCoat.quantity;

    delete[] this->size;
    this->size = new char[strlen(trencchCoat.size) + 1];
    strcpy_s(this->size, strlen(trencchCoat.size) + 1, trencchCoat.size);

    delete[] this->color;
    this->color = new char[strlen(trencchCoat.color) + 1];
    strcpy_s(this->color, strlen(trencchCoat.color) + 1, trencchCoat.color);

    delete[] this->photograph;
    this->photograph = new char[strlen(trencchCoat.photograph) + 1];
    strcpy_s(this->photograph, strlen(trencchCoat.photograph) + 1, trencchCoat.photograph);

    return *this;
}

char* TrencchCoat::getPhotograph() const
{
    return this->photograph;
}

char* TrencchCoat::getSize() const {
    return this->size;
}

char* TrencchCoat::getColor() const {
    return this->color;
}

int TrencchCoat::getPrice() const {
    return this->price;
}

int TrencchCoat::getQuantity() const {
    return this->quantity;
}

void TrencchCoat::setSize(const std::string& size) {
    if (this->size)
        delete[] this->size;
    this->size = new char[size.length() + 1];
    strcpy_s(this->size, size.length() + 1, size.c_str());
}

void TrencchCoat::setColor(const std::string& color) {
    if (this->color)
        delete[] this->color;
    this->color = new char[color.length() + 1];
    strcpy_s(this->color, color.length() + 1, color.c_str());
}

void TrencchCoat::setPrice(int price) {
    this->price = price;
}

void TrencchCoat::setQuantity(int quantity) {
    this->quantity = quantity;
}

void TrencchCoat::setPhotograph(const std::string& photograph) {
    if (this->photograph)
        delete[] this->photograph;
    this->photograph = new char[photograph.length() + 1];
    strcpy_s(this->photograph, photograph.length() + 1, photograph.c_str());
}




void TrencchCoat::toString(const TrencchCoat& trencchCoat) {
    std::cout << "Size: " << trencchCoat.size << ", Color: " << trencchCoat.color << ", Price: " << trencchCoat.price
              << ", Quantity: " << trencchCoat.quantity << ", Photograph: " << trencchCoat.photograph << "\n";
}

