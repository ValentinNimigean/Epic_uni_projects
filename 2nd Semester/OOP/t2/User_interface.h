//
// Created by valen on 4/24/2024.
//

#ifndef OOP_T2_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
#define OOP_T2_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
#include "Service.h"


class Ui{
private:
    RealEstateAgency &agency;

public:
    Ui(RealEstateAgency &agency);
    ~Ui()=default;

    void run();
};
#endif //OOP_T2_915_NIMIGEAN_VALENTIN_USER_INTERFACE_H
