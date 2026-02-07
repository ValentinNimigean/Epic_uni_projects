//
// Created by valen on 4/3/2024.
//

#ifndef T1_915_NIMIGEAN_VALENTIN_1_REPOSITORY_H
#define T1_915_NIMIGEAN_VALENTIN_1_REPOSITORY_H

#include "Domain.h"
#include <vector>
#include <iostream>
using namespace std;

class Repository {
private:
    std::vector<protein> proteins;
public:
    Repository();
    std::vector<protein> getProteins();
    void deleteProtein(protein p);
    ~Repository();
};

#endif //T1_915_NIMIGEAN_VALENTIN_1_REPOSITORY_H
