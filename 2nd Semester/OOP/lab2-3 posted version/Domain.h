//
// Created by valen on 3/24/2024.
//

#pragma once

typedef struct {
    char* address;
    char* type;
    int price;
    int surface;
    char* owner;
}Estate;

Estate* createEstate(char* address,char* type, int price, int surface, char* owner);
void killEstate(Estate* e);
char* getAddress(Estate* e);
char* getType(Estate* e);
int getPrice(Estate* e);
int getSurface(Estate* e);
char* getOwner(Estate* e);
Estate* copyEstate(Estate* e);
void stringEstate(Estate* e,char str[]);


