//
// Created by valen on 3/27/2024.
//

#ifndef A2_3_915_NIMIGEAN_VALENTIN_UNDO_REDO_H
#define A2_3_915_NIMIGEAN_VALENTIN_UNDO_REDO_H

#include "Dynamic_arrray.h"
#include "Repository.h"

typedef struct {
    Estate* estate;
    int operationType;
} Operation;

Operation* createOperation(Estate* e, int operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
int getOperationType(Operation* o);
Estate* getEstate_undo_redo(Operation* o);




typedef struct {
    DynamicArray* operations;
} UndoRedo;

UndoRedo* createUndoRedo();
void destroyUndoRedo(UndoRedo* ur);
void push(UndoRedo* ur, Operation* o);
Operation* pop(UndoRedo* ur);
int isEmpty(UndoRedo* ur);




#endif //A2_3_915_NIMIGEAN_VALENTIN_UNDO_REDO_H
