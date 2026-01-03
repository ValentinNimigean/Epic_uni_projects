//
// Created by valen on 3/25/2024.
//
#pragma once
#ifndef A2_3_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#define A2_3_915_NIMIGEAN_VALENTIN_CONTROLLER_H

#include "Dynamic_arrray.h"
#include "Repository.h"
#include "Undo_redo.h"
#include "Domain.h"

typedef struct {
    Repository* repo;
    UndoRedo* undo;
    UndoRedo* redo;
} Controller;

Controller* createController(Repository* repo, UndoRedo* undo, UndoRedo* redo);
void destroyController(Controller* ctrl);
int addEstate_controller(Controller* ctrl, char* address, char* type, int price, int surface, char* owner);
int deleteEstate_controller(Controller* ctrl, char* address);
int updateEstate_controller(Controller* ctrl, char* address, char* type, int price, int surface, char* owner);
DynamicArray* getEstates_controller(Controller* ctrl);
DynamicArray* filterEstates_controller(Controller* ctrl, char* type);
DynamicArray* sortEstates_controller(Controller* ctrl, int (*cmp)(int, int));
int findEstate_controller(Controller* ctrl, char* address);
int undo(Controller* ctrl);
int redo(Controller* ctrl);





#endif //A2_3_915_NIMIGEAN_VALENTIN_CONTROLLER_H
