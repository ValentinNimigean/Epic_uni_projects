//
// Created by valen on 3/27/2024.
//

#include "Undo_redo.h"
#include <stdlib.h>

Operation* createOperation(Estate* e, int operationType){
    Operation* o = (Operation*)malloc(sizeof(Operation));
    if(o == NULL)
        return NULL;
    o->estate = copyEstate(e);
    if(o->estate == NULL)
    {
        free(o);
        return NULL;
    }

    o->operationType = operationType;
    return o;
}

void destroyOperation(Operation* o){
    if(o == NULL)
        return;
    killEstate(o->estate);
    free(o);
}

Operation* copyOperation(Operation* o){
    if(o == NULL)
        return NULL;
    Operation* copy = createOperation(o->estate, o->operationType);
    return copy;
}

int getOperationType(Operation* o){
    return o->operationType;
}

Estate* getEstate_undo_redo(Operation* o){
    return o->estate;
}

UndoRedo* createUndoRedo(){
    UndoRedo* ur = (UndoRedo*)malloc(sizeof(UndoRedo));
    if(ur == NULL)
        return NULL;
    ur->operations = createDynamicArray(10, &destroyOperation);
    return ur;
}

void destroyUndoRedo(UndoRedo* ur){
    if(ur == NULL)
        return;
    destroy_array(ur->operations);
    free(ur);
}

void push(UndoRedo* ur, Operation* o){
    if(ur == NULL || o == NULL)
        return;
    add_dynamic(ur->operations, o);
}

Operation* pop(UndoRedo* ur){
    if(ur == NULL)
        return NULL;
    if(ur->operations->size == 0)
        return NULL;
    Operation* o = (Operation*)ur->operations->elems[ur->operations->size - 1];
    ur->operations->size--;
    return o;
}

int isEmpty(UndoRedo* ur){
    if(ur == NULL)
        return -1;
    return ur->operations->size == 0;
}


