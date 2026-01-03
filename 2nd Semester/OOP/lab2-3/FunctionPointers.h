#pragma once

typedef int (*operation1)(char* , char*);
typedef int (*operation2)(medicine* , int);

int ascending(char* a , char* b);
int descending(char* a , char* b);
int short_supply(medicine* med , int val);
int low_concentration(medicine* med , int val);