//
//  Element.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include "Color.hpp"

#include <iostream>
#include <fstream>
#include <string>

class Element {
protected:
    uint16_t index_;
    std::string designator_;
    uint16_t x_;
    uint16_t y_;
    uint16_t lineWidth_;
    
    Color fillColor_;
    Color lineColor_;
    Color textColor_;

public:
    Element(){};
    virtual ~Element() = default;
    enum type{BULB=1,RESISTOR,SMARTBULB,VARISTOR};

    virtual void printInfo(std::ostream&) const=0;
    virtual void save(std::ofstream&)=0;
    virtual void read(std::ifstream&)=0;
    virtual int getType()=0;
    
    friend std::ostream& operator<<(std::ostream& os,const Element* element) {
        element->printInfo(os);
        return os;
    }

    //getters
    uint32_t getIndex();
    std::string getDesignator();
    uint16_t getX();
    uint16_t getY();
    uint16_t getLineWidth();

    std::string getColorString(uint8_t);
    Color getColor(uint8_t);

    //setters
    bool setIndex(uint32_t);
    bool setDesignator(std::string);
    bool setX(uint16_t);
    bool setY(uint16_t);
    bool setLineWidth(uint16_t);

    void setFillColor(Color);
    void setLineColor(Color);
    void setTextColor(Color);

    //misc methods
    virtual std::string parseSVGdefinition()=0;
};

#endif /* Element_hpp */
