//
// Created by valen on 4/3/2024.
//

#include "Repository.h"
/*
 * Constructor for the Repository class
 */

Repository::Repository(): proteins(0){

    protein p1("Human", "Myosin-2", "MSSDSEV");
    protein p2("Human", "Keratin", "VTLIPHAREFAIRE");
    protein p3("Mouse", "Keratin", "TCGGGSGCGPR");
    protein p4("E-Coli", "tufA", "MVTLIHP");
    protein p5("E-Coli", "cspE", "MVTLIHP");
    proteins.push_back(p1);
    proteins.push_back(p2);
    proteins.push_back(p3);
    proteins.push_back(p4);
    proteins.push_back(p5);

}


std::vector<protein> Repository::getProteins()
{
    return proteins;
}

void Repository::deleteProtein(protein p)
{
    for (int i = 0; i < proteins.size(); i++)
    {
        if (proteins[i] == p)
        {
            proteins.erase(proteins.begin() + i);

            return;

        }
    }
}

Repository::~Repository() = default;





