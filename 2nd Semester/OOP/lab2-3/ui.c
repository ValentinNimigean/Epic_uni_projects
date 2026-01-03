#include <stdio.h>
#include <string.h>
#include "domain.h"
#include "repository.h"
#include "controller.h"
#include "FunctionPointers.h"

void ui_add_medicine(meds_repo* repository , undo_redo* undo){
    medicine new_med;
    char name[25];
    int conc, quantity , price;
    printf("\nEnter the medicine's name:");
    scanf("%s" , name);
    printf("\nEnter the medicine's concentration:");
    while(1) {
        scanf("%d" , &conc);
        if(conc >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }
    printf("\nEnter the medicine's price:");
    while(1) {
        scanf("%d" , &price);
        if(price >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }
    printf("\nEnter the medicine's quantity:");
    while(1) {
        scanf("%d" , &quantity);
        if(quantity >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }
    new_med = create_medicine(name , quantity , conc , price);
    add_medicine_controller(repository , new_med , undo);
}

void ui_delete_medicine(meds_repo* repository , undo_redo* undo){
    char name[25];
    int conc;
    printf("\nEnter the name of the medicine you want to remove: ");
    scanf("%s" , name);
    printf("\nEnter the concentration of the medicine you want to remove: ");
    while(1) {
        scanf("%d" , &conc);
        if(conc >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }
    delete_medicine_controller(repository , undo , name , conc);
}

void ui_update_medicine(meds_repo* repository , undo_redo* undo){
    char name[25] , old_name[25];
    int old_conc , conc , quant , price;
    printf("\nEnter the name of the medicine you want to update:");
    scanf("%s" , old_name);
    printf("\nEnter the concentration of the medicine you want to update:");
    while(1) {
        scanf("%d", &old_conc);
        if(old_conc >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }

    printf("\nEnter the new name, or '-1' if you want to keep the previous name:");
    scanf("%s" , name);
    printf("\nEnter the new concentration, or '-1' if you want to keep the previous concentration:");
    while(1) {
        scanf("%d" , &conc);
        if(conc >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }

    printf("\nEnter the new quantity, or '-1' if you want to keep the previous quantity:");
    while(1) {
        scanf("%d" , &quant);
        if(quant >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }

    printf("\nEnter the new price, or '-1' if you want to keep the previous price:");
    while(1) {
        scanf("%d" , &price);
        if(price >= 0)
            break;
        printf("\nPlease enter a valid value\n>");

        char ch;
        while ((ch = getchar()) != '\n');
    }

    update_medicine_controller(repository , undo , old_name , old_conc , name , conc , quant , price);
}

void ui_print_medicines_containing_a_given_string(meds_repo* repository){

    printf("\nEnter the string: ");
    char str[25] , ch;
    int i = 0;
    while ((ch = getchar()) != '\n');

    while ((ch = getchar()) != '\n') {
        str[i] = ch;
        i++;
    }

    printf("Do you want to sort the list ascending or descending?\n> ");
    char opt[25];
    while(1){
        scanf("%s" , opt);
        if (strcmp(opt , "ascending") == 0) {
            controller_sort(repository, &ascending);
            break;
        }
        if(strcmp(opt , "descending") == 0) {
            controller_sort(repository, &descending);
            break;
        }
        else
            printf("\nPlease enter a valid option!\n>");
        while ((ch = getchar()) != '\n');
    }
    str[i] = '\0';
    for (int i = 0 ; i < repository->size ; i++){
        if (verify_matching_string(repository->med[i].name , str) == 1)
            printf("------------Medicine number %d -----------"
                   "\nName: %s\nConcentration: %d\nQuantity: %d\nPrice: %d\n\n\n"
                   ,i , get_name(&repository->med[i]) , get_concentration(&repository->med[i])
                   , get_quantity(&repository->med[i]) , get_price(&repository->med[i]));
    }
}

void ui_print_medicines_in_short_supply(meds_repo* repository){
    int val;
    int option = 0;
    printf("\n1.See medicines that are in a lower quantity than a value");
    printf("\n2.See medicines that have a lower concentration than a value\n");

    while (1) {
        char ch;
        scanf("%d", &option);
        if (option == 1 || option == 2)
            break;
        else
            printf("\nPlease enter a valid option!\n>");
        while ((ch = getchar()) != '\n');
    }

    operation2 op;
    if (option == 1)
        op = &short_supply;
    else
        op = &low_concentration;

    printf("\nEnter the value: ");
    scanf("%d" , &val);
    for (int i = 0 ; i < repository->size ; i++){
        if (op(&repository->med[i] , val) == 1) {
            printf("------------Medicine number %d -----------"
                   "\nName: %s\nConcentration: %d\nQuantity: %d\nPrice: %d\n\n\n", i, get_name(&repository->med[i]),
                   get_concentration(&repository->med[i]), get_quantity(&repository->med[i]),
                   get_price(&repository->med[i]));
        }
    }
}

void ui_start(meds_repo* repository , undo_redo* undo , undo_redo* redo){
    printf("Hello! Please choose one of the options below!\n\n\n");
    while(1){
        printf("1. Add a new medicine"
               "\n2. Delete an existing medicine"
               "\n3. Update an existing medicine"
               "\n4. Print all medicines that contains a given string"
               "\n5. See medicines depending on a filter"
               "\n6. Undo"
               "\n7. Redo"
               "\n0. Exit\n\n");
        printf("> ");
        int option = -1;
        while (1) {
            char ch;
            scanf("%d", &option);
            if (option >= 0 && option <= 7)
                break;
            else
                printf("\nPlease enter a valid option!\n>");
            while ((ch = getchar()) != '\n');
        }
        if (option == 0)
            break;
        else{
            switch(option){
                case(1):{
                    ui_add_medicine(repository , undo);
                    break;
                }
                case(2):{
                    ui_delete_medicine(repository , undo);
                    break;
                }
                case(3):{
                    ui_update_medicine(repository , undo);
                    break;
                }
                case(4):{
                    ui_print_medicines_containing_a_given_string(repository);
                    break;
                }
                case(5):{
                    ui_print_medicines_in_short_supply(repository);
                    break;
                }
                case(6):{
                    if (undo->size <= 0)
                        printf("You cannot undo anymore!\n\n\n");
                    else
                        undo_controller(repository , undo , redo);
                    break;
                }
                case(7):{
                    if (redo->size <= 0)
                        printf("You cannot redo anymore!\n\n\n");
                    else
                        redo_controller(repository , redo , undo);
                    break;
                }
            }
        }
    }
}
