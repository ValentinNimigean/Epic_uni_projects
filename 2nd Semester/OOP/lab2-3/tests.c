#include "domain.h"
#include "repository.h"
#include "controller.h"
#include <string.h>
#include <assert.h>

void test_domain(){
    medicine med;
    med = create_medicine("parasinus" , 23 , 30 ,2);
    assert(strcmp("parasinus" , get_name(&med)) == 0);
    assert(get_concentration(&med) == 30);
    assert(get_price(&med) == 2);
    assert(get_quantity(&med) == 23);
}

void test_repository(){
    meds_repo* meds;
    undo_redo* undo;
    meds = createMedicineDynamicArray(1);
    assert(meds->capacity == 1);
    undo = createUndoRedoArray(1);
    assert(undo->capacity == 1);
    add_medicine(meds , create_medicine("parasinus" , 23 , 30 ,2), undo);
    assert(strcmp("parasinus" , get_name(&meds->med[0])) == 0);
    assert(get_concentration(&meds->med[0]) == 30);
    assert(get_price(&meds->med[0]) == 2);
    assert(get_quantity(&meds->med[0]) == 23);
    assert(meds->size == 1);

    update_medicine_repository(meds , undo , 0 , "tantum" , -1 , 60 , 22);
    assert(strcmp("tantum" , get_name(&meds->med[0])) == 0);
    assert(get_concentration(&meds->med[0]) == 30);
    assert(get_price(&meds->med[0]) == 22);
    assert(get_quantity(&meds->med[0]) == 60);
    assert(meds->size == 1);


    delete_medicine(meds , undo , 0);
    assert(meds->size == 0);

    destroy_dynamic_array(meds);
    destroy_undo_redo(undo);
}

void test_controller(){
    assert (verify_matching_string("abba" , "a") == 1);
    assert (verify_matching_string("abba" , "ab") == 1);
    assert (verify_matching_string("abba" , "abb") == 1);
    assert (verify_matching_string("abba" , "abba") == 1);
    assert (verify_matching_string("abba" , "aba") == 0);

    meds_repo* meds;
    undo_redo* undo;
    meds = createMedicineDynamicArray(5);
    undo  = createUndoRedoArray(5);
    add_medicine_controller(meds , create_medicine("parasinus" , 23 , 30 ,2) , undo);
    add_medicine_controller(meds , create_medicine("alala" , 23 , 30 ,2) , undo);
    add_medicine_controller(meds , create_medicine("babs" , 23 , 30 ,2) , undo);

    assert(strcmp("parasinus" , get_name(&meds->med[0])) == 0);
    assert(strcmp("alala" , get_name(&meds->med[1])) == 0);
    assert(strcmp("babs" , get_name(&meds->med[2])) == 0);

    controller_sort(meds , ascending);

    assert(strcmp("alala" , get_name(&meds->med[0])) == 0);
    assert(strcmp("babs" , get_name(&meds->med[1])) == 0);
    assert(strcmp("parasinus" , get_name(&meds->med[2])) == 0);

    destroy_dynamic_array(meds);
    destroy_undo_redo(undo);
}

void run_all_tests(){
    test_domain();
    test_repository();
    test_controller();
}