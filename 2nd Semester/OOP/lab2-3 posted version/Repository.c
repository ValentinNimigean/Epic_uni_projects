//
// Created by valen on 3/25/2024.
//

#include "Repository.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

Repository* createRepository(){
    Repository* repo=malloc(sizeof(Repository));
    if(repo==NULL)
        return NULL;
    repo->estates=createDynamicArray(10,&killEstate);
    return repo;
}

void destroyRepository(Repository* repo){
    if(repo==NULL)
        return;

    destroy_array(repo->estates);

    free(repo);
}

int addEstate_repo(Repository* repo, Estate* e){
    if(repo==NULL || e==NULL)
        return 0;
    add_dynamic(repo->estates,e);
    return 1;
}

int findEstate_repo(Repository* repo, char* address){
    if(repo==NULL || address==NULL)
        return -1;
    for(int i=0;i<repo->estates->size;i++){
        Estate* e=(Estate*)repo->estates->elems[i];
        if(strcmp(e->address,address)==0)
            return i;
    }
    return -1;
}

int deleteEstate_repo(Repository* repo, char* address){
    if(repo==NULL || address==NULL)
        return 0;
    int pos=findEstate_repo(repo,address);
    if(pos==-1)
        return 0;
    delete_dynamic(repo->estates,pos);
    return 1;
}


int updateEstate_repo(Repository* repo, char* address, char* type, int price, int surface, char* owner){
    if(repo==NULL || address==NULL || type==NULL || owner==NULL)
        return 0;
    int pos=findEstate_repo(repo,address);
    if(pos==-1)
        return 0;
    Estate* e=(Estate*)repo->estates->elems[pos];
    e->price=price;
    e->surface=surface;
    free(e->type);
    e->type=malloc(sizeof(char)*(strlen(type)+1));
    if(e->type==NULL)
        return 0;
    strcpy(e->type,type);
    free(e->owner);
    e->owner=malloc(sizeof(char)*(strlen(owner)+1));
    if(e->owner==NULL)
        return 0;
    strcpy(e->owner,owner);
    return 1;
}

DynamicArray* getEstates_repo(Repository* repo){
    if(repo==NULL)
        return NULL;
    return repo->estates;
}

