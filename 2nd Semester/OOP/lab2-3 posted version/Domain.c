//
// Created by valen on 3/24/2024.
//

#include "Domain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Estate* createEstate(char* address,char* type, int price, int surface, char* owner){

    Estate* e=malloc(sizeof(Estate));
    if(e==NULL)
        return NULL;
    e->address= malloc(sizeof(char)*(strlen(address)+1));
    if (e->address==NULL){
        free(e);
        return NULL;
    }
    strcpy(e->address,address);
    e->type= malloc(sizeof(char)*(strlen(type)+1));
    if (e->type==NULL){
        free(e);
        return NULL;
    }
    strcpy(e->type,type);
    e->price=price;
    e->surface=surface;
    e->owner= malloc(sizeof(char)*(strlen(owner)+1));
    if (e->owner==NULL){
        free(e);
        return NULL;
    }
    strcpy(e->owner,owner);
    return e;


}
void killEstate(Estate* e){
    if(e==NULL)
        return;
    free(e->address);
    free(e->type);
    free(e->owner);
    free(e);
}
char* getAddress(Estate* e){
    if(e==NULL)
        return NULL;

    return e->address;

}
char* getType(Estate* e){
    if(e==NULL)
        return NULL;

    return e->type;

}
int getPrice(Estate* e){
    if(e==NULL)
        return -1;

    return e->price;

}
int getSurface(Estate* e){
    if(e==NULL)
        return -1;

    return e->surface;

}
char* getOwner(Estate* e){
    if(e==NULL)
        return NULL;

    return e->owner;
}



Estate* copyEstate(Estate* e){

    if(e==NULL)
        return NULL;
    Estate* e_new= createEstate(getAddress(e), getType(e), getPrice(e), getSurface(e), getOwner(e));
    return e_new;

}
void stringEstate(Estate* e,char str[]){
    if (e==NULL)
        return;
    sprintf(str,"Address: %s , Type: %s , Price: %d , Surface: %d , Owner: %s ", e->address,e->type,e->price,e->surface,e->owner);


}

