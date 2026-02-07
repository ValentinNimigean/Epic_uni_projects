//
// Created by valen on 5/29/2024.
//

#ifndef OOP_T3_915_NIMIGEAN_VALENTIN_SERVICE_H
#define OOP_T3_915_NIMIGEAN_VALENTIN_SERVICE_H
#include "Repository.h"

class Service{
private:
    Repository* repository;

public:
    Service(Repository* repo){
        repository=repo;
    }
    QList<Exercise> get_list(){
        QList<Exercise> list;
        list=repository->get_list();
        std::sort(list.begin(),list.end(),[](Exercise e1,Exercise e2){return e1.get_start()<e2.get_start();});

                return list;


    }
    QList<Exercise> filter(int level){
        QList<Exercise> list;
        list=repository->get_list();
        QList<Exercise>new_list;
        for(Exercise e :list)
            if(e.get_intensity()>level)
                new_list.append(e);


        return new_list;

    }


};

#endif //OOP_T3_915_NIMIGEAN_VALENTIN_SERVICE_H
