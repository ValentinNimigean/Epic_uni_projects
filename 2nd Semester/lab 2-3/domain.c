#include "domain.h"
#include <string.h>

medicine create_medicine(char* name , int quantity , int concentration , int price){
    medicine med;
    strcpy(med.name , name);
    med.quantity = quantity;
    med.concentration = concentration;
    med.price = price;

    return med;
}

char* get_name(medicine* med){
    return med->name;
}

int get_concentration(medicine* med){
    return med->concentration;
}

int get_price(medicine* med){
    return med->price;
}

int get_quantity(medicine* med){
    return med->quantity;
}

void update_name(medicine* med , char* name){
    strcpy(med->name , name);
}

void update_concentration(medicine* med , int concentration){
    med->concentration = concentration;
}

void update_price(medicine* med , int price){
    med->price = price;
}

void update_quantity(medicine* med , int quantity){
    med->quantity = quantity;
}
