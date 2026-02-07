//
// Created by valen on 4/24/2024.
//

#include "User_interface.h"
#include <iostream>
using namespace std;
void Ui::run() {
    std::cout<<"Choose one of the following"<<std::endl;
    std::cout<<"1. Remove a client"<<std::endl;
    std::cout<<"2. Show all clients"<<std::endl;
    std::cout<<"3. add a dwelling"<<std::endl;
    std::cout<<"4. Save to file"<<std::endl;
    std::cout<<"5. Exit"<<std::endl;


    while (true){

        int command;
        std::cin>>command;
        if (command==1){
            std::string name;
            std::cout<<"Enter the name of the client you want to remove"<<std::endl;
            std::cin>>name;
            this->agency.removeClient(name);
        }
        if (command==2){
            std::vector<Client*>clients=this->agency.getClients();
            for (auto &client : clients){
                std::cout<<client->toString()<<std::endl;
            }
        }
        if (command==3){
            std::string name;

        }
        if (command==4){
            this->agency.saveToFile();
        }
        if (command==5){
            break;
        }
    }




}

Ui::Ui(RealEstateAgency &agency) : agency(agency) {

}

