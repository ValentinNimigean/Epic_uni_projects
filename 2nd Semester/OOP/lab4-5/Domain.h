//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_DOMAIN_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_DOMAIN_H
#include <string>
using namespace std;
class TrencchCoat {
private:
    char* size;
    char* color;
    int price;
    int quantity;
    char* photograph;
public:
    TrencchCoat();
    TrencchCoat(const std::string& size, const std::string& color, int price, int quantity, const std::string& photograph);
    TrencchCoat(const TrencchCoat& trencchCoat);
    ~TrencchCoat();
    TrencchCoat& operator=(const TrencchCoat& trencchCoat);
    bool operator==(const TrencchCoat& trencchCoat);
    char *getPhotograph() const;
    char *getSize() const;
    char *getColor() const;
    int getPrice() const;
    int getQuantity() const;
    void setSize(const std::string& size);
    void setColor(const std::string& color);
    void setPrice(int price);
    void setQuantity(int quantity);
    void setPhotograph(const std::string& photograph);


   void toString(const TrencchCoat& trencchCoat);
};

#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_DOMAIN_H
