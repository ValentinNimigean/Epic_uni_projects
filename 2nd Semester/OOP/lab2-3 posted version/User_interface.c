//
// Created by valen on 3/27/2024.
//

#include "User_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dynamic_arrray.h"
#include "Pointer.h"


UI* createUI(Controller* ctrl){
    UI* ui = (UI*)malloc(sizeof(UI));
    if(ui == NULL)
        return NULL;
    ui->ctrl = ctrl;
    return ui;
}

void destroyUI(UI* ui){
    if(ui == NULL)
        return;
    free(ui);
}

int read_int(){
    char s[100];
    int x;

        printf("Enter the number: ");
        scanf("%s", s);
        x = atoi(s);
        if(x != 0)
            return x;

    printf("Invalid number!\n");
    return -1;
}



void addEstate_UI(UI* ui){
    char address[100], type[100], owner[100];
    int price, surface;
    printf("Enter the address: ");

    scanf("%s", address);
    if(findEstate_controller(ui->ctrl, address) != -1){
        printf("Estate already exists!\n");
        return;
    }
    printf("Enter the type: ");
    scanf("%s", type);
    if(strcmp(type, "house") != 0 && strcmp(type, "penthouse") != 0 && strcmp(type, "apartment") != 0 && strcmp(type, "studio") != 0){
        printf("Invalid type!\n");
        return;
    }
    printf("Enter the price: ");
    price = read_int();
    if(price == -1)
        return;
    printf("Enter the surface: ");
    surface = read_int();
    if(surface == -1)
        return;
    printf("Enter the owner: ");
    scanf("%s", owner);
    int res = addEstate_controller(ui->ctrl, address, type, price, surface, owner);
    if(res == 0)
        printf("Invalid estate!\n");
    printf("Estate added successfully!\n");
}

void deleteEstate_UI(UI* ui){
    char address[100];
    printf("Enter the address: ");
    scanf("%s", address);
    int res = deleteEstate_controller(ui->ctrl, address);
    if(res == 0)
        printf("Invalid estate!\n");
    printf("Estate deleted successfully!\n");
}

void updateEstate_UI(UI* ui){
    char address[100], type[100], owner[100];
    int price, surface;
    printf("Enter the address: ");
    scanf("%s", address);
    if(findEstate_controller(ui->ctrl, address) == -1){
        printf("Estate does not exist!\n");
        return;
    }
    printf("Enter the new type: ");
    scanf("%s", type);
    if(strcmp(type, "house") != 0 && strcmp(type, "penthouse") != 0 && strcmp(type, "apartment") != 0 && strcmp(type, "studio") != 0){
        printf("Invalid type!\n");
        return;
    }
    printf("Enter the new price: ");
    price = read_int();
    if(price == -1)
        return;
    printf("Enter the new surface: ");
    surface = read_int();
    if(surface == -1)
        return;
    printf("Enter the new owner: ");
    scanf("%s", owner);
    int res = updateEstate_controller(ui->ctrl, address, type, price, surface, owner);
    if(res == 0)
    {printf("Invalid estate!\n");
        return;}
    printf("Estate updated successfully!\n");
}

void listEstates_UI(UI* ui){


    printf("Would you like to sort the estates ascending(1),or descending(2)?:\n");
    int x = read_int();

    if(x == 1){
        DynamicArray* arr=sortEstates_controller(ui->ctrl, &price_ascending);
        for(int i = 0; i < arr->size; i++){
            Estate* e = (Estate*)arr->elems[i];
            char str[1000];
            stringEstate(e, str);
            printf("%s\n", str);
        }
        destroy_array(arr);

    }
    if(x == 2){
        DynamicArray* arr=sortEstates_controller(ui->ctrl, &price_descending);
        for(int i = 0; i < arr->size; i++){
            Estate* e = (Estate*)arr->elems[i];
            char str[1000];
            stringEstate(e, str);
            printf("%s\n", str);
        }
        destroy_array(arr);
    }
    if(x != 1 && x != 2){
        printf("Invalid command!\n");
        return;
    }

}

void filterEstates_UI(UI* ui){
    char type[100];
    printf("Enter the type: ");
    scanf("%s", type);
    if(strcmp(type, "house") != 0 && strcmp(type, "penthouse") != 0 && strcmp(type, "apartment") != 0 && strcmp(type, "studio") != 0){
        printf("Invalid type!\n");
        return;
    }
    DynamicArray* arr = filterEstates_controller(ui->ctrl, type);
    if(arr == NULL)
        return;
    for(int i = 0; i < arr->size; i++){
        Estate* e = (Estate*)arr->elems[i];
        char str[1000];
        stringEstate(e, str);
        printf("%s\n", str);
    }
    destroy_array(arr);
}

void undo_UI(UI* ui){
    int res = undo(ui->ctrl);
    if(res == 0)
        printf("No more undos!\n");
    printf("Undo successful!\n");
}

void redo_UI(UI* ui){
    int res = redo(ui->ctrl);
    if(res == 0)
        printf("No more redos!\n");
    printf("Redo successful!\n");
}

void printMenu(){
    printf("Welcome to my epic estate manager :3!\n");
    printf("Here are your options:\n");
    printf("1. Add estate\n");
    printf("2. Delete estate\n");
    printf("3. Update estate\n");
    printf("4. List all estates\n");
    printf("5. Filter estates\n");
    printf("6. Undo\n");
    printf("7. Redo\n");
    printf("0. Exit\n");
}


void startUI(UI* ui){
    printMenu();
    while(1){

        char cmd[100];
        printf("Enter your command: ");
        scanf("%s", cmd);

        if(strcmp(cmd, "exit") == 0)
            return;
        if(strcmp(cmd, "add") == 0)
            addEstate_UI(ui);

        if(strcmp(cmd, "delete") == 0)
            deleteEstate_UI(ui);

        if(strcmp(cmd, "update") == 0)
            updateEstate_UI(ui);

        if(strcmp(cmd, "list") == 0)
            listEstates_UI(ui);

        if(strcmp(cmd, "filter") == 0)
            filterEstates_UI(ui);

        if(strcmp(cmd, "undo") == 0)
            undo_UI(ui);

        if(strcmp(cmd, "redo") == 0)
            redo_UI(ui);

        if((strcmp(cmd, "exit") != 0)&&(strcmp(cmd, "add") != 0)&&(strcmp(cmd, "delete") != 0)&&(strcmp(cmd, "update") != 0)&&(strcmp(cmd, "list") != 0)&&(strcmp(cmd, "filter") != 0)&&(strcmp(cmd, "undo") != 0)&&(strcmp(cmd, "redo") != 0))

            printf("Invalid command!\n");




    }
}


