//
// Created by valen on 4/3/2024.
//

#include "Tests.h"
#include <assert.h>

#include "Repository.h"
#include "Domain.h"
#include "Controller.h"

void Tests::test_hardcode_proteins() {
    Repository repository_test;
    assert(repository_test.getProteins().size() == 5);
    printf("Test passed\n");
}

void Tests::test_delete_protein() {
    Repository repository;
    Controller controller(repository);
    controller.deleteProtein_controller("Human", "Keratin");
    assert(repository.getProteins().size() == 5);
    printf("Test passed\n");
}


void Tests::test_show_proteins_by_name_and_sort_by_protein_name_and_sequence_lenght() {
    Repository repository;
    Controller controller(repository);
    std::vector<protein> proteins_test = controller.get_proteins_by_name_and_sort_by_protein_name_and_sequence_lenght("K");

    assert(proteins_test.size() == 0);

    printf("Test passed\n");
}



void Tests::test_all() {
    test_hardcode_proteins();
    test_delete_protein();
    test_show_proteins_by_name_and_sort_by_protein_name_and_sequence_lenght();

}
