//
// Created by valen on 4/24/2024.
//

#ifndef OOP_T2_915_NIMIGEAN_VALENTIN_SERVICE_H
#define OOP_T2_915_NIMIGEAN_VALENTIN_SERVICE_H


#include <vector>
#include "Domain.h"

class RealEstateAgency{
private:
    std::vector<Client*>clients;
    std::vector<Dwelling*>dwellings;
public:
    RealEstateAgency()=default;
    ~RealEstateAgency()=default;

    void addDwelling(Dwelling* d);


    std::vector<Client *> getClients();
    std::string get_interestedCLients(Dwelling &d);
    void addClient(Client *c);

    void saveToFile();

    void removeClient(std::string name);
};


#endif //OOP_T2_915_NIMIGEAN_VALENTIN_SERVICE_H
