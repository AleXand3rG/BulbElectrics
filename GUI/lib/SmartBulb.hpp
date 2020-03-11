//
//  SmartBulb.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef SmartBulb_hpp
#define SmartBulb_hpp

#include "Element.hpp"
#include "Bulb.hpp"
#include "Color.hpp"

#include <iostream>
#include <fstream>
#include <string>

class SmartBulb : public Bulb {
protected:
    uint16_t intensity_;

public:
    SmartBulb(){}
    SmartBulb(uint16_t,uint16_t);
    SmartBulb(uint32_t,std::string,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,Color,Color,Color,bool,uint16_t);
    ~SmartBulb() override = default;
    
    static uint32_t type_;
    static Element* createSmartBulb() {return new SmartBulb();}

    void printInfo(std::ostream&) const override;
    void read(std::ifstream&) override;
    void save(std::ofstream&) override;
    uint32_t getType() override;

    //getters
    uint16_t getIntensity();

    //setters
    bool setIntensity(uint16_t);

    //misc methods
    std::string parseSVGdefinition() override;
};

#endif /* SmartBulb_hpp */
