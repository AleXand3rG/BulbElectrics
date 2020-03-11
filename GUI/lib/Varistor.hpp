//
//  Varistor.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//
#ifndef Varistor_hpp
#define Varistor_hpp

#include "Element.hpp"
#include "Resistor.hpp"
#include "Color.hpp"

#include <iostream>
#include <fstream>
#include <string>

class Varistor : public Resistor {
protected:
    float clampingVoltage_;
    
public:
    Varistor(){}
    Varistor(uint16_t,uint16_t);
    Varistor(uint32_t,std::string,uint16_t,uint16_t,uint16_t,std::string,Color,Color,Color,float);
    ~Varistor() override = default;
    static Element* createVaristor() {return new Varistor();}
    static uint32_t type_;
    
    void printInfo(std::ostream&) const override;
    void read(std::ifstream&) override;
    void save(std::ofstream&) override;
    uint32_t getType() override;
    
    //getters
    float getClampingVoltage();
    
    //setters
    bool setClampingVoltage(float);
    
    //misc methods
    std::string parseSVGdefinition() override;
};

#endif /* Varistor_hpp */
