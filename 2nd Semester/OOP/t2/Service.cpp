//
// Created by valen on 4/24/2024.
//

#include "Service.h"
#include <fstream>

void RealEstateAgency::addDwelling(Dwelling *d) {
    dwellings.push_back(d);

}

std::string RealEstateAgency::get_interestedCLients(Dwelling &d) {
    std::string s;
for(auto &client:clients){
        if(client->isInterested(d))
            s+=client->toString();
    }
    return s;
}

std::vector<Client*> RealEstateAgency::getClients(){
    return this->clients;
}

void RealEstateAgency::addClient(Client *c) {
    clients.push_back(c);
}


void RealEstateAgency::saveToFile() {
    std::ofstream file("clients.txt");
    for(auto &client:clients){
        file<<client->toString()<<std::endl;
    }
    file.close();
}

void RealEstateAgency::removeClient(std::string name) {
    for (int i=0;i<clients.size();i++){
        if(clients[i]->get_name()==name){
            clients.erase(clients.begin()+i);
            return;
        }
    }
}




