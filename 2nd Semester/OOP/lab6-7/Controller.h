//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#include "Repository.h"
#include "File_writer.h"
#include "SQL_repo.h"
class Controller {
private:


  Repository repository;
  File_writer* file_writer;



public:

    //default constructor
    Controller() ;
    explicit Controller(Repository &repository,File_writer* file_writer);


    //constructor with parameters


    //removes a coat from the repository
    void removeCoat_Controller(const std::string& photograph);

    //updates a coat from the repository

    void addCoat_Controller(TrencchCoat& coat);

    int findCoat_Controller(const std::string& photo);



   void update_list_user_mode_controller(std::vector<TrencchCoat> list);


    std::vector<TrencchCoat> listCoats_Controller();

    void updateCoat_Controller(TrencchCoat &coat);

    void save_basket_to_file(std::vector<TrencchCoat> list);

    void open_basket();


};

#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
