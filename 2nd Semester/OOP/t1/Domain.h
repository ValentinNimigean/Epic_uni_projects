//
// Created by valen on 4/3/2024.
//


#ifndef T1_915_NIMIGEAN_VALENTIN_1_DOMAIN_H
#define T1_915_NIMIGEAN_VALENTIN_1_DOMAIN_H

#include <string>
#include <vector>
#include <iostream>

class protein {
private:

    std::string organism;
    std::string name;
    std::string sequence;
public:
    protein();
    protein(std::string organism, std::string name, std::string sequence);
    std::string getOrganism();
    std::string getName();
    std::string getSequence();
    bool operator==(const protein& p);
    ~protein();
};



#endif //T1_915_NIMIGEAN_VALENTIN_1_DOMAIN_H
