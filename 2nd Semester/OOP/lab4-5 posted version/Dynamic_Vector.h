

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_DYNAMIC_VECTOR_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_DYNAMIC_VECTOR_H
#pragma once

#include "Domain.h"

template <typename TElement>
class DynamicVector
{
private:
    TElement* elems;
    int size;
    int capacity;

public:

    DynamicVector(int capacity=10)
    {
        this->size = 0;
        this->capacity = capacity;
        this->elems = new TElement[capacity];
    }





     DynamicVector(const DynamicVector& v)
    {
        this->size = v.size;
        this->capacity = v.capacity;
        this->elems = new TElement[this->capacity];
        for (int i = 0; i < this->size; i++)
            this->elems[i] = v.elems[i];
    }

    ~DynamicVector()
    {
        delete[] this->elems;
    }





    void add(const TElement& e) {
        if (this->size == this->capacity)
            this->resize();
        this->elems[this->size] = e;
        this->size++;
    }

    void remove(const TElement& e) {
        int i = 0;
        for (i = 0; i < this->size; i++)
            if (this->elems[i] == e)
                break;
        for (int j = i; j < this->size - 1; j++)
            this->elems[j] = this->elems[j + 1];
        this->size--;

    }


    void update(const TElement& e, const TElement& new_e) {
        for (int i = 0; i < this->size; i++)
            if (this->elems[i] == e)
                this->elems[i] = new_e;

    }



    TElement& operator[](int pos)
    {
        return this->elems[pos];
    }



    DynamicVector& operator=(const DynamicVector& v)
    {
        if (this == &v)
            return *this;

        this->size = v.size;
        this->capacity = v.capacity;

        delete[] this->elems;
        this->elems = new TElement[this->capacity];
        for (int i = 0; i < this->size; i++)
            this->elems[i] = v.elems[i];

        return *this;
    }

    int getSize() const {
        return this->size;
    }








private:
    // Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    void resize(int factor = 2)
    {
        this->capacity *= factor;

        TElement* els = new TElement[this->capacity];
        for (int i = 0; i < this->size; i++)
            els[i] = this->elems[i];

        delete[] this->elems;
        this->elems = els;
    }
};




#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_DYNAMIC_VECTOR_H
