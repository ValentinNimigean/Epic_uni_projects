#pragma once

void ui_start(meds_repo* repo , undo_redo* undo , undo_redo* redo);
void ui_add_medicine(meds_repo* repo , undo_redo* undo);
void ui_delete_medicine(meds_repo* repo , undo_redo* undo);
void ui_update_medicine(meds_repo* repo , undo_redo* undo);
void ui_print_medicines_containing_a_given_string(meds_repo* repo);
void ui_print_medicines_in_short_supply(meds_repo* repo);
void redo_controller(meds_repo* repository , undo_redo* redo , undo_redo* undo);