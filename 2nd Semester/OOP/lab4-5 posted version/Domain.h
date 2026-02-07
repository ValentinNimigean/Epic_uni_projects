//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_DOMAIN_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_DOMAIN_H
#include <string>
using namespace std;
class TrencchCoat {
private:
    std::string size;
    std::string color;
    int price;
    int quantity;
    std::string photograph;
public:
    TrencchCoat();
    TrencchCoat(const std::string& size, const std::string& color, int price, int quantity, const std::string& photograph);
    TrencchCoat(const TrencchCoat& trencchCoat);
    ~TrencchCoat();

    TrencchCoat& operator=(const TrencchCoat& trencchCoat);
    bool operator==(const TrencchCoat& trencchCoat);
    std::string getPhotograph() const;
    std::string getSize() const;
    std::string getColor() const;
    int getPrice() const;
    int getQuantity() const;
    void setSize(const std::string& size);
    void setColor(const std::string& color);
    void setPrice(int price);
    void setQuantity(int quantity);
    void setPhotograph(const std::string& photograph);


};

#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_DOMAIN_H
