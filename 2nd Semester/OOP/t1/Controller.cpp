//
// Created by valen on 4/3/2024.
//

#include "Controller.h"
#include "Repository.h"
#include <string>
#include <cstring>
Controller::Controller(Repository &repository): repository(repository) {}
/*
 * Function that adds a protein to the repository
 * @param organism - string
 * @param name - string
 * @param sequence - string
 */
void Controller::deleteProtein_controller(std::string organism, std::string name) {
    std::vector<protein> proteins = repository.getProteins();
    for (auto & p : proteins) {
        if (p.getOrganism() == organism && p.getName() == name) {
            repository.deleteProtein(p);

            return;
        }
    }

}
std::vector<protein> Controller::getProteins() {
    return repository.getProteins();
}
/*
 * Function that returns all proteins that have the given name in their organism name
 * @param name - string
 * @return vector<protein>
 */
std::vector<protein> Controller::get_proteins_by_name_and_sort_by_protein_name_and_sequence_lenght(std::string name) {
    std::vector<protein> proteins = repository.getProteins();
    std::vector<protein> result;
    for (auto & p : proteins) {
        if (std::string(p.getOrganism()).find(name) != std::string::npos)
            result.push_back(p);
        }

    return result;
}

bool Controller::find(std::string organism, std::string name) {
    std::vector<protein> proteins = repository.getProteins();
    for (auto & p : proteins) {
        if (p.getOrganism() == organism && p.getName() == name) {
            return true;
        }
    }
    return false;

}
Controller::~Controller() = default;
