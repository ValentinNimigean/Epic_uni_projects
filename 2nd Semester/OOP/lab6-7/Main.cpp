//
// Created by valen on 3/26/2024.
//
#include "Domain.h"
#include <iostream>
#include <cstring>

#include "Repository.h"
#include "Controller.h"
#include "User_interface.h"
#include "Tests.h"

int main(){

    Repository repository;
    repository.readFromFile("repo.txt");

    cout<<"Welcome to my epic trenchcoat shop :3:"<<endl;
    cout<<"wich type of file do you want to save the basket in? (csv/html)"<<endl;
    string file_type;
    cin>>file_type;
    File_writer* file_writer;
    if(file_type == "csv")
        file_writer = new CSV_file;
    else if(file_type == "html")
        file_writer = new HTML_file;
    else
    {
        cout<<"Invalid file type!"<<endl;
        return 0;
    }





    Controller controller{repository,file_writer};
    User_interface user_interface{controller};
    complete_test();


    user_interface.run();
    return 0;
}