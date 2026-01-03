//
// Created by valen on 3/25/2024.
//

#include "COntroller.h"
#include "Repository.h"
#include "Undo_redo.h"
#include "Domain.h"
#include "Dynamic_arrray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Controller* createController(Repository* repo, UndoRedo* ud, UndoRedo* ur){
    Controller* ctrl = (Controller*)malloc(sizeof(Controller));
    if(ctrl == NULL)
        return NULL;
    ctrl->repo = repo;
    ctrl->undo = ur;
    ctrl->redo = ud;
    return ctrl;
}





void destroyController(Controller* ctrl){
    if(ctrl == NULL)
        return;
    destroyRepository(ctrl->repo);
    destroyUndoRedo(ctrl->undo);
    destroyUndoRedo(ctrl->redo);
    free(ctrl);
}

int addEstate_controller(Controller* ctrl, char* address, char* type, int price, int surface, char* owner){
    if(ctrl == NULL || address == NULL || type == NULL || owner == NULL)
        return 0;
    Estate* e = createEstate(address, type, price, surface, owner);
    if(e == NULL)
        return 0;
    Operation* o = createOperation(copyEstate(e), 1);
    addEstate_repo(ctrl->repo, e);
    push(ctrl->undo, o);
    return 1;
}

int deleteEstate_controller(Controller* ctrl, char* address){
    if(ctrl == NULL || address == NULL)
        return 0;
    int pos = findEstate_repo(ctrl->repo, address);
    if(pos == -1)
        return 0;
    Estate* e = (Estate*)ctrl->repo->estates->elems[pos];
    Operation* o = createOperation(copyEstate(e), 2);
    deleteEstate_repo(ctrl->repo, address);
    push(ctrl->undo, o);
    return 1;
}

int updateEstate_controller(Controller* ctrl, char* address, char* type, int price, int surface, char* owner){
    if(ctrl == NULL || address == NULL || type == NULL || owner == NULL)
        return 0;
    int pos = findEstate_repo(ctrl->repo, address);
    if(pos == -1)
        return 0;
    Estate* e = (Estate*)ctrl->repo->estates->elems[pos];
    Estate* copy = copyEstate(e);
    Operation* o = createOperation(copy, 3);
    updateEstate_repo(ctrl->repo, address, type, price, surface, owner);
    push(ctrl->undo, o);
    return 1;
}


DynamicArray* getEstates_controller(Controller* ctrl){
    if(ctrl == NULL)
        return NULL;
    return getEstates_repo(ctrl->repo);
}


DynamicArray* filterEstates_controller(Controller* ctrl, char* type){
    if(ctrl == NULL || type == NULL)
        return NULL;
    DynamicArray* filtered = createDynamicArray(10, &killEstate);
    for(int i = 0; i < ctrl->repo->estates->size; i++){
        Estate* e = copyEstate(ctrl->repo->estates->elems[i]);
        if(strcmp(e->type, type) == 0)
            add_dynamic(filtered, e);
    }
    return filtered;
}

int findEstate_controller(Controller* ctrl, char* address){
    if(ctrl == NULL || address == NULL)
        return 0;
    int pos = findEstate_repo(ctrl->repo, address);
    if(pos == -1)
        return -1;
    return 1;
}


DynamicArray* sortEstates_controller(Controller* ctrl, int (*cmp)(int , int)){
    if(ctrl == NULL || cmp == NULL)
        return NULL;
    DynamicArray* sorted = createDynamicArray(10, &killEstate);
    printf("getsize:%d\n", get_size(ctrl->repo->estates));
    for(int i = 0; i < get_size(ctrl->repo->estates); i++){
        Estate* e = copyEstate(get_dynamic(ctrl->repo->estates, i));
        add_dynamic(sorted, e);
    }
    for(int i = 0; i < sorted->size - 1; i++){
        for(int j = i + 1; j < sorted->size; j++){
            Estate* e1 = (Estate*)sorted->elems[i];
            Estate* e2 = (Estate*)sorted->elems[j];
            if(cmp(getPrice(e1), getPrice(e2)) == 1){
                Estate* aux = e1;
                sorted->elems[i] = sorted->elems[j];
                sorted->elems[j] = aux;
            }
        }
    }
    return sorted;
}


int undo(Controller* ctrl){
    if(ctrl == NULL)
        return 0;
    if (ctrl->undo->operations->size == 0)
        return 0;

    Operation* o = pop(ctrl->undo);
    if(o == NULL)
        return 0;
    Estate* e = copyEstate( getEstate_undo_redo(o));
    if(getOperationType(o) == 1){
        deleteEstate_repo(ctrl->repo, e->address);
        push(ctrl->redo, createOperation(e, 1));
    }
    if(getOperationType(o) == 2){
        addEstate_repo(ctrl->repo, e);
        push(ctrl->redo, createOperation(e, 2));
    }
    if(getOperationType(o) == 3){
        printf("address:%s,type:%s,price:%d,surface:%d,owner:%s\n", e->address, e->type, e->price, e->surface, e->owner);
        Estate* copy = copyEstate(e);
        updateEstate_repo(ctrl->repo, e->address, copy->type, copy->price, copy->surface, copy->owner);
        push(ctrl->redo, createOperation(copy, 3));
    }
    destroyOperation(o);
    return 1;
}


int redo(Controller* ctrl){
    if(ctrl == NULL)
        return 0;
    Operation* o = pop(ctrl->redo);
    if(o == NULL)
        return 0;
    Estate* e = getEstate_undo_redo(o);
    Estate *copy = copyEstate(e);

    if(getOperationType(o) == 1){
        addEstate_repo(ctrl->repo, copy);
        push(ctrl->undo, createOperation(copy, 2));
        destroyOperation(o);

    }
    if(getOperationType(o) == 2 ){
        deleteEstate_repo(ctrl->repo, copy->address);
        push(ctrl->undo, createOperation(copy, 1));
        destroyOperation(o);
    }
    if(getOperationType(o) == 3){

        updateEstate_repo(ctrl->repo, e->address, copy->type, copy->price, copy->surface, copy->owner);
        push(ctrl->undo, createOperation(copy, 3));
        destroyOperation(o);
    }

    return 1;
}














