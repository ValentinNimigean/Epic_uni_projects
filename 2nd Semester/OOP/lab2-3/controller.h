#pragma once

#include "FunctionPointers.h"

void add_medicine_controller(meds_repo* repository , medicine new_med , undo_redo* undo);
void undo_controller(meds_repo* repository , undo_redo* undo , undo_redo* redo);
int verify_matching_string(char* a,  char* b);
void delete_medicine_controller(meds_repo* repository , undo_redo* undo , char* name , int concentration);
void controller_sort(meds_repo* repository , operation1 op);
void redo_controller(meds_repo* repository , undo_redo* redo , undo_redo* undo);
void update_medicine_controller(meds_repo* repository , undo_redo* undo , char* old_name , int old_conc , char* name , int conc , int quantity , int price);
void generate_random_medicines(meds_repo* repo , undo_redo* undo);