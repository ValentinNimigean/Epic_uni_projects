#pragma once

typedef struct {
    char name[50];
    int quantity , concentration , price;
}medicine;

medicine create_medicine(char* name , int quantity , int concentration , int price);
char* get_name(medicine* med);
int get_quantity(medicine* med);
int get_price(medicine* med);
int get_concentration(medicine* med);
void update_name(medicine* med , char* name);
void update_quantity(medicine* med , int quantity);
void update_concentration(medicine* med , int concentration);
void update_price(medicine* med , int price);

