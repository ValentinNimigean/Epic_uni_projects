//
// Created by valen on 5/29/2024.
//

#ifndef OOP_T3_915_NIMIGEAN_VALENTIN_REPOSITORY_H
#define OOP_T3_915_NIMIGEAN_VALENTIN_REPOSITORY_H


#include <QList>
#include <QFile>
#include <QTextStream>
#include "Domain.h"

class  Repository{

private:
    QList<Exercise> sports;
public:
    Repository(){
        this->load_from_file();
    }
    QList<Exercise> load_from_file(){

        QFile file("sport.txt");
        if(!file.open(QIODevice::ReadOnly)){
            return sports;
        }
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line=in.readLine();
            QStringList fields=line.split(";");
            int start=fields[0].toInt();
            int end=fields[1].toInt();
            QString type=fields[2];
            int intensity=fields[3].toInt();
            QString description=fields[4];
            Exercise e(start,end,type,intensity,description);
            sports.append(e);



        }
        file.close();
        return sports;
    }
    QList<Exercise> get_list(){
        return sports;
    }
};

#endif //OOP_T3_915_NIMIGEAN_VALENTIN_REPOSITORY_H
