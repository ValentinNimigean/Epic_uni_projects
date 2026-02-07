//
// Created by valen on 3/26/2024.
//

#ifndef OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#define OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
#include "Repository.h"
#include "File_writer.h"
typedef struct {
    std::string action;
    TrencchCoat coat;
}   Action;

class Controller {
private:


    Repository repository;
    File_writer* file_writer;
    std::vector<Action> undo_stack;
    std::vector<Action> redo_stack;
    std::vector<TrencchCoat> basket;


public:

    //default constructor
    Controller() ;
    Controller(File_writer* file_writer);
    Controller(Repository &repository,File_writer* file_writer);
    ~Controller();


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

    std::string undo();

    std::string redo();

    vector<TrencchCoat> getTrenchCoatsBySize(string basicString);

    void update_basket(TrencchCoat coat);

    vector<TrencchCoat> getBasket();
};

#endif //OOP_A4_5_915_NIMIGEAN_VALENTIN_CONTROLLER_H
