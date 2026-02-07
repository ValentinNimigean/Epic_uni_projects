//
// Created by valen on 4/3/2024.
//

#ifndef T1_915_NIMIGEAN_VALENTIN_1_CONTROLLER_H
#define T1_915_NIMIGEAN_VALENTIN_1_CONTROLLER_H

#include "Repository.h"

class Controller {
private:
    Repository repository;
    public:
    Controller(Repository &repository);
    void deleteProtein_controller(std::string organism, std::string name);
    std::vector<protein> getProteins();
    std::vector<protein> get_proteins_by_name_and_sort_by_protein_name_and_sequence_lenght(std::string organism);
    bool find(std::string organism, std::string name);
    ~Controller();
};

#endif //T1_915_NIMIGEAN_VALENTIN_1_CONTROLLER_H
