//
// Created by valen on 3/27/2024.
//


using namespace std;
#include "User_interface.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>


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
    char size[100], color[100], photograph[100];
    int price, quantity;
    cout<<"Enter the size: ";
    cin>>size;
    if(strcmp(size, "XS") != 0 && strcmp(size, "S") != 0 && strcmp(size, "M") != 0 && strcmp(size, "L") != 0 && strcmp(size, "XL") != 0 && strcmp(size, "XXL") != 0)
    {
        cout<<"Invalid size."<<endl;
        return;
    }

    cout<<"Enter the color: ";
    cin>>color;
    cout<<"Enter the price: ";
    price= read_number();
    if(price == -1)
        return;
    cout<<"Enter the quantity: ";
    quantity = read_number();
    if(quantity== -1)
        return;
    cout<<"Enter the photograph: ";
    cin>>photograph;
    if(this->controller.findCoat_Controller(photograph) != -1)
    {
        cout<<"The coat already exists."<<endl;
        return;
    }
    this->controller.addCoat_Controller(size, color, price, quantity, photograph);
}

void User_interface::removeCoat_UI() {
    char photograph[100];
    cout<<"Enter the photograph: ";
    cin>>photograph;
    if(this->controller.findCoat_Controller(photograph) == -1)
    {
        cout<<"The coat does not exist."<<endl;
        return;
    }
    this->controller.removeCoat_Controller(photograph);
}

void User_interface::updateCoat_UI() {
    char size[100], color[100], photograph[100], photograph_1[100];
    int price, quantity;
    cout<<"Enter the photograph: ";

    cin>>photograph;
    if(this->controller.findCoat_Controller(photograph) == -1)
    {
        cout<<"The coat does not exist."<<endl;
        return;
    }
    cout<<"Enter the new size: ";
    cin>>size;
    if(strcmp(size, "XS") != 0 && strcmp(size, "S") != 0 && strcmp(size, "M") != 0 && strcmp(size, "L") != 0 && strcmp(size, "XL") != 0 && strcmp(size, "XXL") != 0)
    {
        cout<<"Invalid size."<<endl;
        return;
    }
    cout<<"Enter the new color: ";
    cin>>color;
    cout<<"Enter the new price: ";
    price= read_number();
    if(price == -1)
        return;
    cout<<"Enter the quantity: ";
    quantity = read_number();
    if(quantity== -1)
        return;


    this->controller.updateCoat_Controller(photograph,size, color, price, quantity);
}

void User_interface::listCoats_UI() {
    DynamicVector<TrencchCoat>coats = this->controller.listCoats_Controller();
    for (int i = 0; i < coats.getSize(); i++) {
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


void User_interface::user_mode(){
    cout<<"Welcome to the trenchcoat shop! :3"<<endl;
    std::string size;
    size="invalid";
    while (size!="XXS" && size!="XS" && size!="S" && size!="M" && size!="L" && size!="XL" && size!="XXL" && size!="")
    {cout<<"Please enter the size you want to buy: ";

    cin>>size;
    if (size!="XXS" && size!="XS" && size!="S" && size!="M" && size!="L" && size!="XL" && size!="XXL"&& size!="")
        cout<<"Invalid size! Please enter a valid size."<<endl;
    }

    DynamicVector<TrencchCoat> coats = this->controller.buildShoppingBasket(size);
    cout<<"The coats available in the size you want are: "<<endl;
    int prices=0;
    for (int i = 0; i < coats.getSize(); i++)
    {
        if (coats[i].getSize()==size)
        {
            TrencchCoat coat = coats[i];
            cout<<"Size: "<<coat.getSize()<<", Color: "<<coat.getColor()<<", Price: "<<coat.getPrice()<<", Quantity: "<<coat.getQuantity()<<", Photograph: "<<coat.getPhotograph()<<endl;
            cout<<"Do you want to buy this coat? (yes/no)"<<endl;
            std::string answer;
            cin>>answer;
            if (answer=="yes")
            {prices+=coat.getPrice();
                coats[i].setQuantity(coat.getQuantity()-1);
                cout<<"The coat has been added to your shopping basket."<<endl;
            }
        }

    }





    cout<<"The total price of the coats in your shopping basket is: "<<prices<<endl;
    cout<<"Do you want to buy the cart? (yes/no)"<<endl;
    std::string answer;
    cin>>answer;
    if (answer=="yes")
    {
        cout<<"The cart has been bought."<<endl;
        this->controller.update_list_user_mode_controller(coats);
    }
    else
        cout<<"The cart has not been bought."<<endl;


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
            this->addCoat_UI();
        else if(command == 2)
            this->removeCoat_UI();
        else if(command == 3)
            this->updateCoat_UI();
        else if(command == 4)
            this->listCoats_UI();
        else if(command == 5)
            break;
        else
            cout<<"Invalid command."<<endl;
    }
}

void User_interface::hard_Coded()
{
    this->controller.addCoat_Controller("XS", "red", 100, 5, "a");
    this->controller.addCoat_Controller("S", "blue", 200, 3, "b");
    this->controller.addCoat_Controller("M", "green", 300, 2, "c");
    this->controller.addCoat_Controller("L", "yellow", 400, 1, "d");
    this->controller.addCoat_Controller("XL", "black", 500, 4, "e");
    this->controller.addCoat_Controller("XXL", "white", 600, 6, "f");
    this->controller.addCoat_Controller("XS", "red", 100, 5, "g");
    this->controller.addCoat_Controller("S", "blue", 200, 3, "h");
    this->controller.addCoat_Controller("M", "green", 300, 2, "i");
    this->controller.addCoat_Controller("L", "yellow", 400, 1, "j");
    this->controller.addCoat_Controller("XL", "black", 500, 4, "k");
    this->controller.addCoat_Controller("XXL", "white", 600, 6, "l");
    this->controller.addCoat_Controller("XS", "red", 100, 5, "m");
    this->controller.addCoat_Controller("S", "blue", 200, 3, "n");
    this->controller.addCoat_Controller("M", "green", 300, 2, "o");
    this->controller.addCoat_Controller("L", "yellow", 400, 1, "p");
    this->controller.addCoat_Controller("XL", "black", 500, 4, "q");
    this->controller.addCoat_Controller("XXL", "white", 600, 6, "r");
    this->controller.addCoat_Controller("XS", "red", 100, 5, "s");
    this->controller.addCoat_Controller("S", "blue", 200, 3, "t");
    this->controller.addCoat_Controller("M", "green", 300, 2, "u");
}







