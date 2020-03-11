//
//  Bulb.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef Bulb_hpp
#define Bulb_hpp

#include "Element.hpp"
#include "Color.hpp"

#include <iostream>
#include <fstream>
#include <string>

class Bulb : public Element {
protected:
    uint16_t radius_;
    uint16_t wattage_;
    bool state_;

public:
    Bulb(){};
    Bulb(uint16_t,uint16_t);
    Bulb(uint32_t,std::string,uint16_t,uint16_t,uint16_t,uint16_t,float,Color,Color,Color,bool);
    ~Bulb() = default;
    
    static uint32_t type_;
    static Element* createBulb() {return new Bulb();}

    virtual void printInfo(std::ostream&) const override;
    virtual void read(std::ifstream&) override;
    virtual void save(std::ofstream&) override;
    virtual int getType() override;

    //getters
    uint16_t getRadius();
    uint16_t getWattage();
    bool getState();

    //setters
    bool setRadius(uint16_t);
    bool setWattage(uint16_t);
    bool setState(bool);
    
    //misc methods
    virtual std::string parseSVGdefinition() override;
};

#endif /* Bulb_hpp */
