//
// Created by valen on 4/24/2024.
//

#include "Domain.h"

double Dwelling::getPrice() const {
    return price;
}

bool Dwelling::isValid() const {

    if(this->isProfitable)
        return true;
    return false;
}

Dwelling::Dwelling(double price, bool isProfitable) {
    this->isProfitable=isProfitable;
    this->price=price;

}


double Client::totalIncome() const {
    return this->income;
}

std::string Client::toString() {
    std::string s;
    return s;
}

bool Client::isInterested(Dwelling &d) const {

   if (d.getPrice()/1000<= this->income)
       return true;
    return false;
}

Client::Client(std::string name, double income) {
    this->name=name;
    this->income=income;

}
Person::Person(std::string name, double income) : Client(name, income) {

}

double Person::totalIncome() const {
    return Client::totalIncome();
}

bool Person::isInterested(Dwelling &d) const {

    return Client::isInterested(d);
}

std::string Person::toString() {
    std::string s;
    s+="Name"+ this->name+"\nIncome:"+std::to_string(this->income);
    return s;
}

Company::Company(std::string name, double income,double investment) : Client(name, income) {
    this->moneyFromInvestments=investment;
}


double Company::totalIncome() const {
    return this->income+ this->moneyFromInvestments;
}

bool Company::isInterested(Dwelling &d) const {
    if (d.getPrice()/100<=totalIncome()&&d.isValid())
        return true;
    return false;
}
std::string Client::get_name() {
    return this->name;
}


std::string Company::toString() {
    std::string s;
    s+="Name"+ this->name+"\nIncome:"+std::to_string(this->income)+"\nInvestment:"+std::to_string(this->moneyFromInvestments);
    return s;
}
