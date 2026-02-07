//
// Created by valen on 4/28/2024.
//

#ifndef OOP_A6_7_915_NIMIGEAN_VALENTIN_FILE_WRITER_H
#define OOP_A6_7_915_NIMIGEAN_VALENTIN_FILE_WRITER_H

#endif //OOP_A6_7_915_NIMIGEAN_VALENTIN_FILE_WRITER_H
#include <vector>
#include "Domain.h"

class File_writer{
public:
    virtual void save_to_file(std::vector <TrencchCoat> coats);
    virtual void open_file();

};


class CSV_file:public File_writer{

public:
    void save_to_file(std::vector <TrencchCoat> coats) override;
    void open_file() override;
};

class HTML_file:public File_writer{

public:
    void save_to_file(std::vector <TrencchCoat> coats) override;
    void open_file() override;
};

class sql_file:public File_writer{
public:
    void save_to_file(std::vector <TrencchCoat> coats) override;
    void open_file() override;


};