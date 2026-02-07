//
// Created by valen on 4/24/2024.
//
#include "User_interface.h"
#include "Service.h"
int main() {
    RealEstateAgency agency;
    Person* p1=new Person("Valentin", 1000);
    agency.addClient(p1);
    Person* p2=new Person("Andrei", 2000);
    agency.addClient(p2);
    Person* p3=new Person("Mihai", 3000);
    agency.addClient(p3);
    Company* c1=new Company("SRL",12,120);
    agency.addClient(c1);
    Company* c2=new Company("SA",1200,122);
    agency.addClient(c2);



    Ui ui (agency) ;



    ui.run();


    return 0;
}