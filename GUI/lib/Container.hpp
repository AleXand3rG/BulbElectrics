//
//  Container.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef Container_hpp
#define Container_hpp

#include "Element.hpp"
#include "Bulb.hpp"
#include "Resistor.hpp"
#include "SmartBulb.hpp"
#include "Varistor.hpp"

#include <vector>
#include <map>

using createElement=Element*(*)();

class Container {
    std::vector<Element*> elements_;
    static uint32_t counter_;
    
    std::map<uint32_t,createElement> ElementMap_;
    static uint32_t TYPE_;
public:
    Container();
    ~Container();
    
    Element* create(uint32_t);
    uint32_t registerElement(createElement);
    
    bool saveToFile(std::string);
    bool readFromFile(std::string);
    
    //operators
    Container& operator+(Element*);
    Container& operator-(uint32_t);
    Container& operator--();
    
    //getters
    uint32_t getSize();
    std::vector<Element*>& getVector();
    Element* getElementPtr(uint32_t);
    
    //other methods
    bool isEmpty();
    bool isElement(uint32_t);
    void updateIndex();
    static uint32_t getCounterValue() {return counter_;}
    static void resetCounter() {counter_=0;}
};

#endif /* Container_hpp */
