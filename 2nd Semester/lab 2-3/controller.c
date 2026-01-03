#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "domain.h"
#include "repository.h"
#include "FunctionPointers.h"

void add_medicine_controller(meds_repo* repository, medicine new_med , undo_redo* undo){
    /*
     * Function to call the add function from repository
     */
    add_medicine(repository , new_med , undo);
}

void delete_medicine_controller(meds_repo* repository , undo_redo* undo , char* name , int concentration){
    /*
     * Function to get the index of the med we want to delete and to call the function from repo
     */
    int index = -1;
    for (int i = 0 ; i < repository->size ; i++)
        if (strcmp(get_name(&repository->med[i]) , name) == 0)
            if (get_concentration(&repository->med[i]) == concentration)
                index = i;
    if (index != -1)
        delete_medicine(repository , undo , index);
}

int verify_matching_string(char* a,  char* b){
    /*
     * Function to check if the strings 'a' and 'b' are the same
     */
    if (strcmp(b , "\0") == 0)
        return 1;
    int n1 = strlen(a);
    int n2 = strlen(b);
    for (int i = 0 ; i < n1 ; i++){
        int j = 0;
        if (a[i] == b[j]){
            int cnt = 0;
            for (int j = 0 , ii = i ; j < n2 && ii < n1 ; j++ , ii++)
                if (a[ii] == b[j])
                    cnt++;
            if (cnt == n2)
                return 1;
        }
    }
    return 0;

}

void update_medicine_controller(meds_repo* repository , undo_redo* undo , char* old_name , int old_conc , char* name , int conc , int quantity , int price){
    /*
     * Function to call the update function from repository with the correct index
     */
    int index = -1;
    for (int i = 0 ; i < repository->size ; i++)
        if (strcmp(get_name(&repository->med[i]) , old_name) == 0)
            if (get_concentration(&repository->med[i]) == old_conc)
                index = i;
    if (index != -1)
        update_medicine_repository(repository , undo , index , name , conc , quantity , price);
}

void controller_sort(meds_repo* repo , operation1 op){
    /*
     * Function to sort ascending/descending the repository by name
     */
    for (int i = 0; i < repo->size - 1 ; i++){
        for (int j = i + 1 ; j < repo->size ; j++){
            if (op(repo->med[i].name , repo->med[j].name) == 1){
                medicine aux = repo->med[i];
                repo->med[i] = repo->med[j];
                repo->med[j] = aux;
            }

        }
    }
}

void generate_random_medicines(meds_repo* repo , undo_redo* undo) {
    /*
     * Function to generate random medicines at program start up
     */
    char* name[25] = {"Parasinus"  , "Nurofen" , "Algocalmin" ,
                      "Tantum" , "Nospa" , "Ibuprofen" , "Mezym" , "Nospa" , "Paracetamol" };


    for (int i = 0; i < 11; i++){
        add_medicine_controller(repo , create_medicine(name[rand() % 9] ,
                                               rand() % 200 , rand() % 101 , rand() % 1000) , undo);
    }
}

void undo_controller(meds_repo* repository , undo_redo* undo , undo_redo* redo){
    /*
     * Function to call the undo function from repository
     */
    undo_repo(repository , undo , redo);
}

void redo_controller(meds_repo* repository , undo_redo* redo , undo_redo* undo){
    /*
     * Function to call the redo function from repository
     */
    redo_repo(repository , redo , undo);
}