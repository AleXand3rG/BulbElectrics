//
//  Resistor.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef Resistor_hpp
#define Resistor_hpp

#include "Element.hpp"
#include "Color.hpp"

#include <iostream>
#include <fstream>
#include <string>

class Resistor : public Element {
protected:
    std::string value_;
public:
    Resistor(){};
    Resistor(uint16_t,uint16_t);
    Resistor(uint32_t,std::string,uint16_t,uint16_t,uint16_t,std::string,Color,Color,Color);
    ~Resistor() = default;
    
    static uint32_t type_;
    static Element* createResistor() {return new Resistor();}

    virtual void printInfo(std::ostream&) const override;
    virtual void read(std::ifstream&) override;
    virtual void save(std::ofstream&) override;
    virtual int getType() override;

    //getters
    std::string getValue();

    //setters
    bool setValue(std::string);

    //misc methods
    virtual std::string parseSVGdefinition() override;
};

#endif /* Resistor_hpp */
