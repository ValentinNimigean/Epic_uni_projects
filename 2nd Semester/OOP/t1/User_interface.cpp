//
// Created by valen on 4/3/2024.
//

#include "User_interface.h"
#include "Controller.h"
#include <iostream>
#include <algorithm>

User_interface::User_interface(Controller &controller): controller(controller) {}

void User_interface::print_menu() {
    std::cout << "1. Delete protein\n";
    std::cout << "2. Get all proteins\n";
    std::cout << "3. Get proteins by name and sorted by protein name and sequence lenght\n";
    std::cout << "4. Exit\n";
}

void User_interface::run() {
    while (true) {
        print_menu();
        int command;
        std::cin >> command;
        if (command == 4) {
            break;
        }
        if (command == 1) {
            std::string organism, name;
            std::cout << "Organism: ";
            std::cin >> organism;
            std::cout << "Name: ";
            std::cin >> name;
            if(controller.find(organism, name) == false) {
                std::cout << "Protein not found\n";
                continue;
            } else
            {controller.deleteProtein_controller(organism, name);
            std::cout << "Protein deleted\n";}
        }
        if (command == 2) {
            std::vector<protein> proteins = controller.getProteins();
            for (auto & p : proteins) {
                std::cout << p.getOrganism() << " " << p.getName() << " " << p.getSequence() << "\n";
            }
        }
        if (command == 3) {
            std::string name;
            std::cout << "GIMME THE NAME: ";
            std::cin >> name;
            std::vector<protein> proteins = controller.get_proteins_by_name_and_sort_by_protein_name_and_sequence_lenght(name);
            if(proteins.empty()) {
                std::cout << "No proteins found\n";
                continue;
            } else{
            std::sort(proteins.begin(), proteins.end(), [](protein &p1, protein &p2) {
                if (p1.getName() == p2.getName()) {
                    return p1.getSequence().size() < p2.getSequence().size();
                }
                return p1.getName() < p2.getName();
            });
            for (auto & p : proteins) {
                std::cout << p.getOrganism() << " " << p.getName() << " " << p.getSequence() << "\n";
            }
        }}
    }
}

User_interface::~User_interface() = default;