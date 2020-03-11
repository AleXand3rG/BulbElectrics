//
//  Color.cpp
//  proe-19l-2
//
//  Created by Piotr Daniel on 29/03/19.
//  Copyright © 2019 Piotr Daniel. All rights reserved.
//

#include "Color.hpp"

#include <iostream>
#include <climits>
#include <cstdint>
#include <string>
#include <cmath>

using namespace std;

//Constructors & Destructors:
//default
Color::Color() {
    r_value = 0;
    g_value = 0;
    b_value = 0;
}
Color::Color(uint8_t _r, uint8_t _g, uint8_t _b){
    r_value = _r;
    g_value = _g;
    b_value = _b;
}
//destuctor
Color::~Color(){
}

//Public methods:
string Color::returnStringValue() const {
    string output = "#";
    uint8_t color_value_table[6] = {static_cast<uint8_t>(r_value/16), static_cast<uint8_t>(r_value%16), static_cast<uint8_t>(g_value/16), static_cast<uint8_t>(g_value%16),                                  static_cast<uint8_t>(b_value/16), static_cast<uint8_t>(b_value%16)};
    string hex_table[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
    for(int i=0;i<6;i++)
        output += hex_table[color_value_table[i]];
    return output;
}
uint8_t Color::returnR() const {
    return r_value;
}
uint8_t Color::returnG() const {
    return g_value;
}
uint8_t Color::returnB() const {
    return b_value;
}
bool Color::setColorByName(string color_name) {return stringtoRGB(color_name);}
bool Color::setCMYK(float C,float M,float Y,float K) {return CMYKtoRGB(C, M, Y, K);}
bool Color::setHSV(uint16_t H,float S,float V) {return HSVtoRGB(H, S, V);}
void Color::setRGB(uint8_t red,uint8_t green,uint8_t blue) {
    r_value = red;
    g_value = green;
    b_value = blue;
}

//Private methods:
bool Color::HSVtoRGB(uint16_t hue,float saturation,float value) {
    if (saturation > 1 || value > 1) return false;
    if (saturation < 0 || value < 0) return false;
    float _r, _g, _b;
    float C = saturation * 1 * value * 1;
    float X = float(C * float(1 - abs(fmod((hue)/60, 2) - 1)));
    float m = value*1 - C;
    if (hue < 60) {
        _r = C;
        _g = X;
        _b = 0.0;
    } else if ((hue >= 60 && hue < 120) || hue == 360) {
        _r = X;
        _g = C;
        _b = 0.0;
    } else if (hue >= 120 && hue < 180) {
        _r = 0.0;
        _g = C;
        _b = X;
    } else if (hue >= 180 && hue < 240) {
        _r = 0.0;
        _g = X;
        _b = C;
    } else if (hue >= 240 && hue < 300) {
        _r = X;
        _g = 0.0;
        _b = C;
    } else if (hue >= 300 && hue < 360) {
        _r = C;
        _g = 0.0;
        _b = X;
    } else return false;
    r_value = uint8_t((_r + m) * 255);
    g_value = uint8_t((_g + m) * 255);
    b_value = uint8_t((_b + m) * 255);
    return true;
}
bool Color::CMYKtoRGB(float cyan,float magenta,float yellow,float black) {
    if (cyan > 1 || magenta > 1 || yellow > 1 || black > 1) return false;
    if (cyan < 0 || magenta < 0 || yellow < 0 || black < 0) return false;
    float _r, _g, _b;
    _r = 255 * (1 - cyan) * (1 - black);
    _g = 255 * (1 - magenta) * (1 - black);
    _b = 255 * (1 - yellow) * (1 - black);
    r_value = uint8_t(_r);
    g_value = uint8_t(_g);
    b_value = uint8_t(_b);
    return true;
}
bool Color::stringtoRGB(string html_color_name) {
    //info about used color names : "These 16 were labelled as sRGB and included in the HTML 3.0 specification, which noted they were "the standard 16 colors supported with the Windows VGA palette"

         if (html_color_name == "White"   || html_color_name == "white")   setRGB (255, 255, 255);
    else if (html_color_name == "Silver"  || html_color_name == "silver")  setRGB (192, 192, 192);
    else if (html_color_name == "Gray"    || html_color_name == "gray")    setRGB (128, 128, 128);
    else if (html_color_name == "Black"   || html_color_name == "black")   setRGB (  0,   0,   0);
    else if (html_color_name == "Red"     || html_color_name == "red")     setRGB (255,   0,   0);
    else if (html_color_name == "Maroon"  || html_color_name == "maroon")  setRGB (128,   0,   0);
    else if (html_color_name == "Yellow"  || html_color_name == "yellow")  setRGB (255, 255,   0);
    else if (html_color_name == "Olive"   || html_color_name == "olive")   setRGB (128, 128,   0);
    else if (html_color_name == "Lime"    || html_color_name == "lime")    setRGB (  0, 255,   0);
    else if (html_color_name == "Green"   || html_color_name == "green")   setRGB (  0, 128,   0);
    else if (html_color_name == "Aqua"    || html_color_name == "aqua")    setRGB (  0, 255, 255);
    else if (html_color_name == "Teal"    || html_color_name == "teal")    setRGB (  0, 128, 128);
    else if (html_color_name == "Blue"    || html_color_name == "blue")    setRGB (  0,   0, 255);
    else if (html_color_name == "Navy"    || html_color_name == "navy")    setRGB (  0,   0, 128);
    else if (html_color_name == "Fuchsia" || html_color_name == "fuchsia") setRGB (255,   0, 255);
    else if (html_color_name == "Purple"  || html_color_name == "purple")  setRGB (128,   0, 128);
    else return false;
    return true;
}
