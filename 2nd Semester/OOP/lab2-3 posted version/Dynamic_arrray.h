//
// Created by valen on 3/24/2024.
//

#pragma once
typedef void* TElem;
typedef void(*DestroyElementFunctionType)(TElem);
typedef struct {
    TElem* elems;
    int size;
    int capacity;
    DestroyElementFunctionType destroyFct;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType fct);
void destroy_array(DynamicArray* arr);
int resize_array(DynamicArray* arr);
void add_dynamic(DynamicArray* arr, TElem elem);
void delete_dynamic(DynamicArray* arr, int pos);
void update_dynamic(DynamicArray* arr, int pos, TElem elem);
TElem get_dynamic(DynamicArray* arr, int pos);
int get_size(DynamicArray* arr);








