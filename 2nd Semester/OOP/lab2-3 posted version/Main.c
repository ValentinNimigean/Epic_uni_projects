#include <stdio.h>
#include "Domain.h"
#include "Pointer.h"
#include "Repository.h"
#include "Controller.h"
#include "Dynamic_arrray.h"
#include "Undo_redo.h"
#include "User_interface.h"
#include "Tests.h"


int main()
{complete_test();



    Repository* repo = createRepository();
    UndoRedo* undo = createUndoRedo();
    UndoRedo* redo = createUndoRedo();
    Controller* ctrl = createController(repo, undo, redo);
    UI* ui = createUI(ctrl);

    addEstate_controller(ctrl, "Strada1", "house", rand()%1000, rand()%1000, "Ion");
    addEstate_controller(ctrl, "Strada2", "apartment", rand()%1000, rand()%1000, "Vasile");
    addEstate_controller(ctrl, "Strada3", "house", rand()%1000, rand()%1000, "Gheorghe");
    addEstate_controller(ctrl, "Strada4", "apartment", rand()%1000, rand()%1000, "Mihai");
    addEstate_controller(ctrl, "Strada5", "house", rand()%1000, rand()%1000, "Andrei");
    addEstate_controller(ctrl, "Strada6", "apartment", rand()%1000, rand()%1000, "Cristi");
    addEstate_controller(ctrl, "Strada7", "penthouse", rand()%1000, rand()%1000, "Marius");
    addEstate_controller(ctrl, "Strada8", "house", rand()%1000, rand()%1000, "Alex");
    addEstate_controller(ctrl, "Strada9", "apartment", rand()%1000, rand()%1000, "George");
    addEstate_controller(ctrl, "Strada10", "house", rand()%1000, rand()%1000, "Mihai");
    addEstate_controller(ctrl, "Strada11", "penthouse", rand()%1000, rand()%1000, "Andrei");

    startUI(ui);
    destroyController(ctrl);
    destroyUI(ui);
    return 0;



}