//
// Created by valen on 5/29/2024.
//

#ifndef OOP_T3_915_NIMIGEAN_VALENTIN_DOMAIN_H
#define OOP_T3_915_NIMIGEAN_VALENTIN_DOMAIN_H
#include <QString>
class Exercise{
private:
    int start;
    int end;
    QString type;
    int intesnity;
    QString description;
public:
    Exercise(int start, int end, QString type, int intesnity, QString description):start{start},end{end},type{type},intesnity{intesnity},description{description}{}

    int get_start(){
        return start;
    }
    int get_end(){
        return  end;
    }
    QString get_type(){
        return type;
    }
    int get_intensity(){
        return intesnity;
    }
    QString get_description(){
        return description;
    }
    QString toSTring(){
        return QString::number(start)+"->"+QString::number(end)+" "+type+" "+QString::number(intesnity)+" "+description;
    }

};

#endif //OOP_T3_915_NIMIGEAN_VALENTIN_DOMAIN_H
