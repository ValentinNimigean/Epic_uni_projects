//
// Created by valen on 3/25/2024.
//
#pragma once

#ifndef A2_3_915_NIMIGEAN_VALENTIN_REPOSITORY_H
#define A2_3_915_NIMIGEAN_VALENTIN_REPOSITORY_H

#include "Dynamic_arrray.h"
#include "Domain.h"
#include "Dynamic_arrray.h"


typedef struct {
    DynamicArray* estates;
} Repository;

Repository* createRepository();
void destroyRepository(Repository* repo);
int addEstate_repo(Repository* repo, Estate* e);
int deleteEstate_repo(Repository* repo, char* address);
int updateEstate_repo(Repository* repo, char* address, char* type, int price, int surface, char* owner);
DynamicArray* getEstates_repo(Repository* repo);
int findEstate_repo(Repository* repo, char* address);



#endif //A2_3_915_NIMIGEAN_VALENTIN_REPOSITORY_H
