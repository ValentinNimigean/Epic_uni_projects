//
// Created by valen on 3/24/2024.
//

#include "Dynamic_arrray.h"
#include <stdlib.h>
#include <string.h>

DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType fct){
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    if(da == NULL)
        return NULL;
    da->elems = (TElem*)malloc(sizeof(TElem) * capacity);
    if(da->elems == NULL){
        free(da);
        return NULL;
    }
    da->size = 0;
    da->capacity = capacity;
    da->destroyFct = fct;
    return da;
}

void destroy_array(DynamicArray* arr){
    if(arr == NULL)
        return;
    for(int i = 0; i < arr->size; i++)
        arr->destroyFct(arr->elems[i]);
    free(arr->elems);
    arr->elems = NULL;
    free(arr);
}

int resize_array(DynamicArray* arr){
    if(arr == NULL)
        return -1;
    arr->capacity *= 2;
    TElem* aux = realloc(arr->elems, arr->capacity * sizeof(TElem));
    if(aux == NULL)
        return -1;
    arr->elems = aux;
    return 0;
}

void add_dynamic(DynamicArray* arr, TElem elem){
    if(arr == NULL)
        return;
    if (arr->elems == NULL)
        return;

    if(arr->size == arr->capacity)
        resize_array(arr);
    arr->elems[arr->size++] = elem;
}

void delete_dynamic(DynamicArray* arr, int pos){
    if(arr == NULL)
        return;
    if(arr->elems == NULL)
        return;
    if(pos < 0 || pos >= arr->size)
        return;
    arr->destroyFct(arr->elems[pos]);
    for(int i = pos; i < arr->size - 1; i++)
        arr->elems[i] = arr->elems[i + 1];
    arr->size--;
}

void update_dynamic(DynamicArray* arr, int pos, TElem elem){
    if(arr == NULL)
        return;
    if(arr->elems == NULL)
        return;
    if(pos < 0 || pos >= arr->size)
        return;
    arr->destroyFct(arr->elems[pos]);
    arr->elems[pos] = elem;
}

int get_size(DynamicArray* arr){
    if(arr == NULL)
        return -1;
    return arr->size;
}

TElem get_dynamic(DynamicArray* arr, int pos){
    if(arr == NULL)
        return NULL;
    if(pos < 0 || pos >= arr->size)
        return NULL;
    return arr->elems[pos];

}





