//
//  Container.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "Container.hpp"
#include "Bulb.hpp"
#include "Resistor.hpp"
#include "SmartBulb.hpp"
#include "Varistor.hpp"

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

//Constructor
Container::Container () {
    //Rejestracja klas
    Bulb::type_ = registerElement(Bulb::createBulb);
    Resistor::type_ = registerElement(Resistor::createResistor);
    SmartBulb::type_ = registerElement(SmartBulb::createSmartBulb);
    Varistor::type_ = registerElement(Varistor::createVaristor);
}
uint32_t Container::counter_ = 0;
//Destructor
Container::~Container() {
    for (unsigned long i=0;i<elements_.size();i++) {
        delete elements_[i];
    }
}

uint32_t Container::TYPE_=1;
Element* Container::create(uint32_t id) {
    map<uint32_t,createElement>::iterator it=ElementMap_.find(id);
    if (it!=ElementMap_.end()) {
        return (it->second)();
    }
    else return nullptr;
}
uint32_t Container::registerElement(createElement lol) {
    ElementMap_.insert(pair<uint32_t,createElement>(TYPE_,lol));
    return TYPE_++;
}

bool Container::saveToFile(string outputPath) {
    ofstream outputFile;
    outputFile.open(outputPath, ios::out);
    if (outputFile) {
        for (unsigned long i=0;i<elements_.size();i++) {
            elements_[i]->save(outputFile);
        }
        outputFile.close();
        return true;
    }
    else {
        string err = "\nERROR: File could not be created\n\n";
        throw err;
    }
}
bool Container::readFromFile(string filePath) {
    ifstream inputFile;
    inputFile.open(filePath,ios::in);
    if (inputFile) {
        uint32_t tmp_type=0;
        string tmp="start";
        Element* tmp_Element=nullptr;
        
        while(tmp!="") {
            getline(inputFile, tmp, '\n');
            if (tmp!="") {
                tmp_type=uint32_t(stoi(tmp));
                tmp_Element = create(tmp_type);
                if (tmp_Element!=nullptr) {
                    tmp_Element->read(inputFile);
                    elements_.push_back(tmp_Element);
                    counter_++;
                }
            }
        }
        inputFile.close();
        return true;
    }
    else {
        string err = "\nERROR: File does not exist\n\n";
        throw err;
    }
}

//operators
Container& Container::operator+(Element* newElement) {
    elements_.push_back(newElement);
    counter_++;
    return *this;
}
Container& Container::operator-(const uint32_t which) {
    if (isElement(which)) {
        for(unsigned long i=which;i<elements_.size();i++) {
            elements_[i] = elements_[i+1];
        }
        this->elements_.erase(elements_.end() - 1); counter_--;
        updateIndex();
    }
    return *this;
}
Container& Container::operator--() {
    if (!isEmpty()) {this->elements_.erase(elements_.end() - 1); counter_--;}
    return *this;
}

//getters
uint32_t Container::getSize() {
    return uint32_t(this->elements_.size());
}
std::vector<Element*>& Container::getVector() {
    return elements_;
}
Element* Container::getElementPtr(uint32_t i) {
    return elements_[i];
}

//other methods
bool Container::isEmpty() {
    if (elements_.size()>0) return false;
    else return true;
}
bool Container::isElement(uint32_t which) {
    if (this->isEmpty()) return false;
    if (which>=this->elements_.size()) return false;
    else return true;
}
void Container::updateIndex() {
    for (uint32_t i=0;i<elements_.size();i++) {
        elements_[i]->setIndex(i);
    }
}
