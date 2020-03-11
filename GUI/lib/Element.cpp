//
//  Element.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "Element.hpp"

using namespace std;

//getters
uint32_t Element::getIndex() {
    return index_;
}
string Element::getDesignator() {
    return designator_;
}
uint16_t Element::getX() {
    return x_;
}
uint16_t Element::getY() {
    return y_;
}
uint16_t Element::getLineWidth() {
    return lineWidth_;
}
string Element::getColorString(uint8_t type) {
    switch (type) {
        case 1: return fillColor_.returnStringValue();
        case 2: return lineColor_.returnStringValue();
        case 3: return textColor_.returnStringValue();
        default: return "#000000";
    }
}
Color Element::getColor(uint8_t type) {
    switch (type) {
        case 1: return fillColor_;
        case 2: return lineColor_;
        case 3: return textColor_;
        default: {Color newColor; newColor.setColorByName("Black"); return newColor;}
    }
}

//setters
bool Element::setIndex(uint32_t _value) {
    index_ = _value;
    if (index_ == _value) return true;
    else return false;
}
bool Element::setDesignator(string _value) {
    designator_ = _value;
    if (designator_ == _value) return true;
    else return false;
}
bool Element::setX(uint16_t _value) {
    if (_value<=1000) x_ = _value;
    if (x_ == _value) return true;
    else return false;
}
bool Element::setY(uint16_t _value) {
    if (_value<=1000) y_ = _value;
    if (y_ == _value) return true;
    else return false;
}
bool Element::setLineWidth(uint16_t _value) {
    if (_value>=1 && _value<=10) lineWidth_ = _value;
    if (lineWidth_ == _value) return true;
    else return false;
}
void Element::setFillColor(Color _value) {
    fillColor_ = _value;
}
void Element::setLineColor(Color _value) {
    lineColor_ = _value;
}
void Element::setTextColor(Color _value) {
    textColor_ = _value;
}
