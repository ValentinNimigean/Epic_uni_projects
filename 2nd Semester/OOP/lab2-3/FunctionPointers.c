#include <string.h>
#include "domain.h"


int ascending(char* a , char* b){
    if (strcmp(a , b) > 0)
        return 1;
    return 0;
}

int descending(char* a , char* b){
    if (strcmp(a , b) < 0)
        return 1;
    return 0;
}

int short_supply(medicine* med , int val){
    if (get_quantity(med) < val)
        return 1;
    return 0;
}

int low_concentration(medicine* med , int val){
    if (get_concentration(med) < val)
        return 1;
    return 0;
}