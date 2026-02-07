//
// Created by valen on 3/27/2024.
//


using namespace std;
#include "User_interface.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include "TrenchCoat_exceptions.h"

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


User_interface::User_interface(Controller &controller) : controller(controller) {}

User_interface::~User_interface() = default;

int User_interface::read_number() {
    char s[100];
    int x;
    cin>>s;
    x = atoi(s);
    if(x != 0)
        return x;
    cout<<"Invalid number!"<<endl;
    return -1;
}


void User_interface::printMenu() {
    cout<<"WELCOME TO MY EPIC TRENCHCOAT SHOP :3:"<<endl;
    cout<<"1. Add a coat."<<endl;
    cout<<"2. Remove a coat."<<endl;
    cout<<"3. Update a coat."<<endl;
    cout<<"4. List all coats."<<endl;
    cout<<"5. Exit."<<endl;
}

void User_interface::addCoat_UI() {
    string size,color,price1,quantity1,photograph;

    cout<<"Enter the size: ";
    cin>>size;
    cout<<"Enter the color: ";
    cin>>color;
    cout<<"Enter the price: ";
    cin>>price1;
    int price;
    if (is_number(price1))
    {price = stoi(price1);

    } else
        throw ValidationInherited("bad interger");


    cout<<"Enter the Quantity: ";
    cin>>quantity1;
    int quantity;
    if (is_number(quantity1))
    {quantity = stoi(quantity1);
    } else
        throw ValidationInherited("bad interger");




    cout<<"Enter the Photograph: ";
    cin>>photograph;
    TrencchCoat coat(size,color,price,quantity,photograph);
    TrencchCoatvalidator::validate(coat);

    this->controller.addCoat_Controller(coat);
}

void User_interface::removeCoat_UI() {
    char photograph[100];
    cout<<"Enter the photograph: ";
    cin>>photograph;
    this->controller.removeCoat_Controller(photograph);
}

void User_interface::updateCoat_UI() {
    string size,color,price1,quantity1,photograph;
    cout<<"Enter the photograph: ";

    cin>>photograph;

    cout<<"Enter the size: ";
    cin>>size;
    cout<<"Enter the color: ";
    cin>>color;
    cout<<"Enter the price: ";
    cin>>price1;
    int price;
    if (is_number(price1))
    {price = stoi(price1);

    } else
        throw ValidationInherited("bad interger");




    cout<<"Enter the Quantity: ";
    cin>>quantity1;
    int quantity;
    if (is_number(quantity1))
    {quantity = stoi(quantity1);

    } else
        throw ValidationInherited("bad interger");


    TrencchCoat coat(size,color,price,quantity,photograph);
    TrencchCoatvalidator::validate(coat);

    this->controller.updateCoat_Controller(coat);



}

void User_interface::listCoats_UI() {
    std::vector<TrencchCoat>coats = this->controller.listCoats_Controller();
    for (int i = 0; i < coats.size(); i++) {
        TrencchCoat coat = coats[i];
        cout<<"Size: "<<coat.getSize()<<", Color: "<<coat.getColor()<<", Price: "<<coat.getPrice()<<", Quantity: "<<coat.getQuantity()<<", Photograph: "<<coat.getPhotograph()<<endl;
    }
}
void User_interface::run() {

    cout<<"Welcome to the trenchcoat shop! :3"<<endl;
    while(true)
    {
        cout<<"1. User mode."<<endl;
        cout<<"2. Admin mode."<<endl;
        cout<<"3. Exit."<<endl;
        int command = read_number();
        if(command == 2)
        {
            cout<<"Enter the admin password: ";
            std::string password;
            cin>>password;
            if(password != "admin321")
            {
                cout<<"Invalid password."<<endl;
                continue;
            }
            else
            admin_mode();}
        else if(command == 3)
            break;
        else if(command == 1)
            this->user_mode();
        else
            cout<<"Invalid command."<<endl;
    }


}


void User_interface::user_mode() {
    cout<<"Welcome to the trenchcoat shop! :3"<<endl;
    while(true)
    {

        cout<<"1. Buy coats."<<endl;
        cout<<"2. open basket.";
        cout<<"3. Exit."<<endl;
        int command = read_number();
        if(command == 2)
            this->controller.open_basket();
        else if(command == 1)
            this->user_mode_basket();
        else if(command == 3)
            break;
        else
            cout<<"Invalid command."<<endl;
    }
}


void User_interface::user_mode_basket(){
    cout<<"Welcome to the trenchcoat shop! :3"<<endl;

    std::string size;
    size="bad";
    std::string size1;
    size1=cin.get();
    while (size!="XXS" && size!="XS" && size!="S" && size!="M" && size!="L" && size!="XL" && size!="XXL" && size!="\n")
    {cout<<"Please enter the size you want to buy: ";
        size=cin.get();

    if (size!="XXS" && size!="XS" && size!="S" && size!="M" && size!="L" && size!="XL" && size!="XXL"&& size!="\n")
        cout<<"Invalid size! Please enter a valid size."<<endl;
    }
    std::vector<TrencchCoat> coats = this->controller.listCoats_Controller();
    cout<<"The coats available in the size you want are: "<<endl;
    int prices=0;
    std::vector<TrencchCoat>basket;


    while (true) {
        for (auto &i: coats) {
            if (i.getSize() == size||size=="\n")
            if(i.getQuantity()!=0){
                TrencchCoat coat = i;
                cout << "Size: " << coat.getSize() << ", Color: " << coat.getColor() << ", Price: " << coat.getPrice()
                     << ", Quantity: " << coat.getQuantity() << ", Photograph: " << coat.getPhotograph() << endl;
                cout << "Do you want to buy this coat? (yes/no)" << endl;
                std::string answer;
                cin >> answer;
                if (answer == "yes") {
                    prices += coat.getPrice();
                    i.setQuantity(coat.getQuantity() - 1);
                    int ok = 0;
                    cout << "The coat has been added to your shopping basket." << endl;
                    for (auto &j: basket) {
                        if (j.getPhotograph() == coat.getPhotograph()) {
                            j.setQuantity(i.getQuantity() + 1);
                            ok = 1;


                        }

                    }
                    if (ok == 0) {
                        basket.push_back(coat);
                    }


                }

            }

        }


        cout << "The total price of the coats in your shopping basket is: " << prices << endl;
        cout << "Do you want to buy the cart? (yes/no/continue)" << endl;
        std::string answer;
        cin >> answer;
        if (answer == "yes") {
            cout << "The cart has been bought." << endl;
            this->controller.update_list_user_mode_controller(coats);
            this->controller.save_basket_to_file(basket);


            return;
        } else if (answer=="no")
        {cout << "The cart has not been bought." << endl;
            this->controller.save_basket_to_file(basket);
            return;}

    }


}

void User_interface::admin_mode() {
    cout<<"Welcome to the admin mode! :3"<<endl;
    while(true)
    {
        printMenu();
        int command = read_number();
        if(command == -1)
            continue;
        if(command == 1)
            try {
                this->addCoat_UI();

            }
        catch (ValidationInherited &ex)
        {
            cout<<ex.what()<<endl;
        }

        else if(command == 2)
            try {
                this->removeCoat_UI();
            }
            catch (ValidationInherited &ex)
            {
                cout<<ex.what()<<endl;
            }
        else if(command == 3)
            try {
                this->updateCoat_UI();
            }
            catch (ValidationInherited &ex)
            {
                cout<<ex.what()<<endl;
            }
        else if(command == 4)
            this->listCoats_UI();
        else if(command == 5)
            break;
        else
            cout<<"Invalid command."<<endl;
    }
}