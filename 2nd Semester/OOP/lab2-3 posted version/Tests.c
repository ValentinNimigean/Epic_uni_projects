//
// Created by valen on 3/27/2024.
//

#include "Tests.h"
#include "Domain.h"
#include "Controller.h"
#include "User_interface.h"
#include "Dynamic_arrray.h"
#include "Repository.h"
#include "Pointer.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void test_createEstate(){
    printf("Test createEstate\n");
    Estate* e = createEstate("address", "type", 100, 100, "owner");
    assert(strcmp(getAddress(e), "address") == 0);
    assert(strcmp(getType(e), "type") == 0);
    assert(getPrice(e) == 100);
    assert(getSurface(e) == 100);
    assert(strcmp(getOwner(e), "owner") == 0);
    killEstate(e);
}

void test_addEstate(){
    printf("Test addEstate_controller\n");
    Repository* repo = createRepository();
    UndoRedo* ur = createUndoRedo();
    UndoRedo* ud = createUndoRedo();
    Controller* ctrl = createController(repo, ur, ud);
    addEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    assert(findEstate_repo(ctrl->repo, "address") != -1);
    destroyController(ctrl);
}

void test_removeEstate_controller(){
    printf("Test removeEstate\n");
    Repository* repo = createRepository();
    UndoRedo* ur = createUndoRedo();
    UndoRedo* ud = createUndoRedo();
    Controller* ctrl = createController(repo, ur, ud);
    addEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    deleteEstate_controller(ctrl, "address");
    assert(findEstate_repo(ctrl->repo, "address") == -1);
    destroyController(ctrl);
}

void test_updateEstate_controller(){
    printf("Test updateEstate\n");
    Repository* repo = createRepository();
    UndoRedo* ur = createUndoRedo();
    UndoRedo* ud = createUndoRedo();
    Controller* ctrl = createController(repo, ur, ud);
    addEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    updateEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    assert(findEstate_repo(ctrl->repo, "address") != -1);
    destroyController(ctrl);
}


void test_findEstate_controller(){
    printf("Test findEstate\n");
    Repository* repo = createRepository();
    UndoRedo* ur = createUndoRedo();
    UndoRedo* ud = createUndoRedo();
    Controller* ctrl = createController(repo, ur, ud);
    addEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    assert(findEstate_controller(ctrl, "address") != -1);
    destroyController(ctrl);
}

void test_undo_controller(){
    printf("Test undo\n");
    Repository* repo = createRepository();
    UndoRedo* ur = createUndoRedo();
    UndoRedo* ud = createUndoRedo();
    Controller* ctrl = createController(repo, ur, ud);
    addEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    undo(ctrl);
    assert(findEstate_repo(ctrl->repo, "address") == -1);
    destroyController(ctrl);
}

void test_redo_controller(){
    printf("Test redo\n");
    Repository* repo = createRepository();
    UndoRedo* ur = createUndoRedo();
    UndoRedo* ud = createUndoRedo();
    Controller* ctrl = createController(repo, ur, ud);
    addEstate_controller(ctrl, "address", "type", 100, 100, "owner");
    undo(ctrl);
    redo(ctrl);
    assert(findEstate_repo(ctrl->repo, "address") != -1);
    destroyController(ctrl);
}



void complete_test(){
    test_createEstate();
    test_addEstate();
    test_removeEstate_controller();
    test_updateEstate_controller();
    test_findEstate_controller();
    test_undo_controller();
    test_redo_controller();
    printf("All tests passed!\n");

}