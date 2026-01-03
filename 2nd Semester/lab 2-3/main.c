#include <stdio.h>
#include "repository.h"
#include "controller.h"
#include "tests.h"
#include "ui.h"

int main() {

    run_all_tests();

    meds_repo* repository = createMedicineDynamicArray(15);
    undo_redo* undo = createUndoRedoArray(1);


    generate_random_medicines(repository , undo);
    destroy_undo_redo(undo);


    undo = createUndoRedoArray(1);
    undo_redo* redo = createUndoRedoArray(1);


    ui_start(repository , undo , redo);

    destroy_dynamic_array(repository);
    destroy_undo_redo(undo);
    destroy_undo_redo(redo);

    return 0;
}
