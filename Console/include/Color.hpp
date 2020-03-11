//
//  Color.hpp
//  proe-19l-2
//
//  Created by Piotr Daniel on 29/03/19.
//  Copyright © 2019 Piotr Daniel. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <iostream>
#include <cstdint>
#include <string>

class Color {
    uint8_t r_value;
    uint8_t g_value;
    uint8_t b_value;
    
    bool HSVtoRGB(uint16_t,float,float);
    bool CMYKtoRGB(float,float,float,float);
    bool stringtoRGB(std::string);
    
public:
    Color();
    ~Color();
    
    std::string returnStringValue() const;
    //returns color value as as standard XML 'string' readable for SVG and HTML
    uint8_t returnR() const;
    uint8_t returnG() const;
    uint8_t returnB() const;
    
    bool setHSV(uint16_t,float,float);
    //sets color value converting in-fly HSV to RGB, sample run is: yourColor.setHSV(275, 0.76, 0.22)
    bool setCMYK(float,float,float,float);
    //sets color value converting in-fly CMYK to RGB, sample run is: yourColor.setCMYK(0.21, 0.12, 0.76, 0.22)
    void setRGB(uint8_t,uint8_t,uint8_t);
    //sets color value converting, sample run is: yourColor.setRGB(125, 237, 51)
    bool setColorByName(std::string);
    //sets color value converting in-fly string color name to RGB value, sample run is yourColor.setColorByName("Teal")
};

#endif /* Color_hpp */
