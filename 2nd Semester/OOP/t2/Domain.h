//
// Created by valen on 4/24/2024.
//
#pragma once
#ifndef OOP_T2_915_NIMIGEAN_VALENTIN_DOMAIN_H
#define OOP_T2_915_NIMIGEAN_VALENTIN_DOMAIN_H

#include <string>

class Dwelling{
private:
    double price;
    bool isProfitable;
public:
    Dwelling (double price,bool isProfitable);
    ~Dwelling()=default;
    double getPrice() const;
    bool isValid() const;


};


class Client{
protected:

    std::string name;
    double income;
public:
    Client(std::string name, double income);
    ~Client()=default;


    virtual double totalIncome() const;
    virtual std::string toString();
    virtual bool isInterested(Dwelling&d) const;

    std::string get_name();
};


class Person:public Client{
public:
    Person(std::string name, double income);
    ~Person()=default;

    double totalIncome() const override;
    std::string toString() override;
    bool isInterested(Dwelling&d) const override;
};

class Company:public Client{
private:
    double moneyFromInvestments;

public:
    Company(std::string name, double income, double investment);
    ~Company()=default;
    double totalIncome() const override;
    std::string toString() override;
    bool isInterested(Dwelling&d) const override;


};

#endif //OOP_T2_915_NIMIGEAN_VALENTIN_DOMAIN_H
