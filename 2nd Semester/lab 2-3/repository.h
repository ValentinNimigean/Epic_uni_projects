#pragma once
#include "domain.h"

typedef struct{
    medicine* med;
    int capacity , size;
}meds_repo;

typedef struct{
    meds_repo* repos;
    int capacity, size;
}undo_redo;

undo_redo* createUndoRedoArray(int capacity);
meds_repo* createMedicineDynamicArray(int capacity);
void destroy_dynamic_array(meds_repo* repository);
void undo_repo(meds_repo*repository , undo_redo* undo , undo_redo* redo);
void destroy_undo_redo(undo_redo* undo);
void redo_repo(meds_repo* repository , undo_redo* redo , undo_redo* undo);
void add_medicine(meds_repo* repository  , medicine t , undo_redo* undo);
void resize_repository_array(meds_repo* repository);
void resize_undo_redo(undo_redo* undo_or_redo);
void delete_medicine(meds_repo* repository , undo_redo* undo , int index);
void update_medicine_repository(meds_repo* repository , undo_redo* undo , int index , char* name , int conc , int quant , int price);