//
// Created by valen on 4/3/2024.
//

#include "Domain.h"

protein::protein() {
    this->organism = "";
    this->name = "";
    this->sequence = "";
}

protein::protein(std::string organism, std::string name, std::string sequence) {
    this->organism = organism;
    this->name = name;
    this->sequence = sequence;
}

std::string protein::getOrganism() {
    return this->organism;
}

std::string protein::getName() {
    return this->name;
}

std::string protein::getSequence() {
    return this->sequence;
}





bool protein::operator==(const protein &p) {
    return this->organism == p.organism && this->name == p.name && this->sequence == p.sequence;
}

protein::~protein() = default;
