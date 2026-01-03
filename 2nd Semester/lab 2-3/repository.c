#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repository.h"
#include "domain.h"

undo_redo* createUndoRedoArray(int capacity)
{
    /*
     * Function to create an undo/redo array
     * Returns the undo/redo array
     */
    undo_redo* undo_or_redo = (undo_redo*)malloc(sizeof(undo_redo));

    if (undo_or_redo == NULL)
        return NULL;

    undo_or_redo->capacity = capacity;
    undo_or_redo->size = 0;

    undo_or_redo->repos = (meds_repo*)malloc(capacity * sizeof(meds_repo));
    for (int i = 0 ; i < undo_or_redo->capacity ; i++)
        undo_or_redo->repos[i].med = (medicine*)malloc(10 * sizeof(medicine));
    if (undo_or_redo->repos == NULL)
        return NULL;

    return undo_or_redo;
}

meds_repo* createMedicineDynamicArray(int capacity)
{
    /*
     * Function to create a medicine array
     * Returns the medicine array
     */
    meds_repo* meds = (meds_repo*)malloc(sizeof(meds_repo));

    if (meds == NULL)
        return NULL;

    meds->capacity = capacity;
    meds->size = 0;

    meds->med = (medicine*)malloc(capacity * sizeof(medicine));

    if (meds->med == NULL)
        return NULL;

    return meds;
}

void destroy_dynamic_array(meds_repo* repository){
    /*
     * Function to free the memory of the dynamic array
     */
    if(repository == NULL)
        return;
    free(repository->med);
    free(repository);
}

void resize_undo_redo(undo_redo* undo_or_redo){
    /*
     * Function to resize the undo/redo array if we don't have enough memory
     */
    if (undo_or_redo == NULL)
        return;
    if(undo_or_redo->repos == NULL)
        return;
    int new_cap = undo_or_redo->capacity * 2;
    meds_repo* aux = (meds_repo *)realloc(undo_or_redo->repos , new_cap * sizeof(meds_repo));
    if (aux == NULL)
        return;

    undo_or_redo->capacity = new_cap;
    undo_or_redo->repos = aux;
}

void resize_repository_array(meds_repo* repository){
    /*
     * Function to resize the repository array if we don't have enough memory
     */
    if (repository == NULL)
        return;
    if(repository->med == NULL)
        return;
    int new_cap = repository->capacity * 2;
    medicine* aux = (medicine*)realloc(repository->med , new_cap * sizeof(medicine));

    if (aux == NULL)
        return;

    repository->capacity = new_cap;
    repository->med = aux;
}

void add_medicine(meds_repo* repository , medicine new_med , undo_redo* undo){
    /*
     * Function to add a medicine to the repository
     */
    if(repository == NULL)
        return;

    if(repository->med == NULL)
        return;

    if (repository->size == repository->capacity)
        resize_repository_array(repository);

    if (undo->size == undo ->capacity)
        resize_undo_redo(undo);

    undo->repos->size = repository->size;
    undo->repos->capacity = repository->capacity;

    for (int i = 0 ; i < repository->size ; i++){
        undo->repos->med[i] = repository->med[i];
    }

    undo->size++;

    repository->med[repository->size] = new_med;
    repository->size++;


}

void delete_medicine(meds_repo* repository , undo_redo* undo , int index){

    /*
     * Function to delete a medicine from repository
     */
    if (undo->size == undo ->capacity)
        resize_undo_redo(undo);

    undo->repos->size = repository->size;
    undo->repos->capacity = repository->capacity;

    for (int i = 0 ; i < repository->size ; i++){
        undo->repos->med[i] = repository->med[i];
    }

    undo->size++;

    for (int i = index; i < repository->size - 1; i++)
        repository->med[i] = repository->med[i + 1];
    repository->size--;



}

void update_medicine_repository(meds_repo* repository , undo_redo* undo , int index , char* name , int conc , int quant , int price){

    /*
     * Function to update the medicine from repository
     */
    if (undo->size == undo ->capacity)
        resize_undo_redo(undo);

    undo->repos->size = repository->size;
    undo->repos->capacity = repository->capacity;

    for (int i = 0 ; i < repository->size ; i++){
        undo->repos->med[i] = repository->med[i];
    }

    undo->size++;


    if (strcmp(name , "-1") != 0)
        update_name(&repository->med[index] , name);
    if (conc != -1)
        update_concentration(&repository->med[index], conc);
    if (quant != -1)
        update_quantity(&repository->med[index], quant);
    if (price != -1)
        update_price(&repository->med[index], price);


}

void undo_repo(meds_repo* repository , undo_redo* undo , undo_redo* redo){

    /*
     * Function to perform the undo
     */
    if (undo->size - 1 >= 0) {
        if (redo->size == redo->capacity)
            resize_undo_redo(redo);
        redo->repos[redo->size] = *repository;
        redo->size++;

        undo->size--;
        *repository = undo->repos[undo->size];
    }
}

void redo_repo(meds_repo* repository , undo_redo* redo , undo_redo* undo){
    /*
     * Function to perform the redo
     */
    if (redo->size - 1 >= 0) {
        redo->size--;
        if (undo->size == undo ->capacity)
            resize_undo_redo(undo);


        undo->repos[undo->size] = *repository;
        undo->size++;
        *repository = redo->repos[redo->size];
    }
}

void destroy_undo_redo(undo_redo* undo){
    /*
     * Function to free the memory for the undo/redo array
     */
    if (undo == NULL)
        return;

    free(undo->repos);
    free(undo);
}