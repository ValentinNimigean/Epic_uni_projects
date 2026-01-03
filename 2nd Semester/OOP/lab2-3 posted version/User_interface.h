//
// Created by valen on 3/27/2024.
//

#ifndef A2_3_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
#define A2_3_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H

#include "Controller.h"

typedef struct {
    Controller* ctrl;
} UI;

UI* createUI(Controller* ctrl);
void destroyUI(UI* ui);
void startUI(UI* ui);
void printMenu();
void printEstates(DynamicArray* arr);
void addEstate_UI(UI* ui);
void deleteEstate_UI(UI* ui);
void updateEstate_UI(UI* ui);
void listEstates_UI(UI* ui);
void filterEstates_UI(UI* ui);
void undo_UI(UI* ui);
void redo_UI(UI* ui);


#endif //A2_3_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
