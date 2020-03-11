//
//  Resistor.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "Resistor.hpp"
#include "Container.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Constructors:
uint32_t Resistor::type_=RESISTOR;
Resistor::Resistor(uint16_t x,uint16_t y) {
    index_ = Container::getCounterValue();
    designator_ = "Default Resistor";
    x_ = x;
    y_ = y;
    lineWidth_ = 2;
    value_ = "?value?";
    fillColor_.setColorByName("Gray");
    lineColor_.setColorByName("Maroon");
    textColor_.setColorByName("Blue");
}
Resistor::Resistor(uint32_t i,string d,uint16_t x,uint16_t y,uint16_t lw,string v,Color FC,Color LC,Color TC) {
    index_ = i;
    designator_ = d;
    x_ = x;
    y_ = y;
    lineWidth_ = lw;
    value_ = v;
    fillColor_ = FC;
    lineColor_ = LC;
    textColor_ = TC;
}

//iostream
void Resistor::printInfo(ostream& os) const {
    os << index_+1 << ". ";
    os << "Designator: " << designator_ << endl;
    os << "Coordinate x: " << x_ << endl;
    os << "Coordinate y: " << y_ << endl;
    os << "Line Width: " << lineWidth_ << endl;
    os << "Value: " << value_ << endl;
    os << "Fill Color: " << fillColor_.returnStringValue() << endl;
    os << "Line Color: " << lineColor_.returnStringValue() << endl;
    os << "Text Color: " << textColor_.returnStringValue() << endl;
    os << endl;
}
void Resistor::save(ofstream& output) {
    output<<type_<<endl;
    output<<designator_<<endl;
    output<<x_<<endl;
    output<<y_<<endl;
    output<<lineWidth_<<endl;
    output<<value_<<endl;
    output<<to_string(fillColor_.returnR())<<endl;
    output<<to_string(fillColor_.returnG())<<endl;
    output<<to_string(fillColor_.returnB())<<endl;
    output<<to_string(lineColor_.returnR())<<endl;
    output<<to_string(lineColor_.returnG())<<endl;
    output<<to_string(lineColor_.returnB())<<endl;
    output<<to_string(textColor_.returnR())<<endl;
    output<<to_string(textColor_.returnG())<<endl;
    output<<to_string(textColor_.returnB())<<endl;
}
void Resistor::read(ifstream& input) {
    string tmp;
    uint8_t tmp_r=0;
    uint8_t tmp_g=0;
    uint8_t tmp_b=0;
    
    getline(input, designator_, '\n');
    getline(input, tmp, '\n');
    x_=uint16_t(stoi(tmp));
    getline(input, tmp, '\n');
    y_=uint16_t(stoi(tmp));
    getline(input, tmp, '\n');
    lineWidth_=uint16_t(stoi(tmp));
    getline(input, value_, '\n');
    getline(input, tmp, '\n');
    tmp_r=uint8_t(stoi(tmp));
    getline(input, tmp, '\n');
    tmp_g=uint8_t(stoi(tmp));
    getline(input, tmp, '\n');
    tmp_b=uint8_t(stoi(tmp));
    fillColor_.setRGB(tmp_r, tmp_g, tmp_b);
    getline(input, tmp, '\n');
    tmp_r=uint8_t(stoi(tmp));
    getline(input, tmp, '\n');
    tmp_g=uint8_t(stoi(tmp));
    getline(input, tmp, '\n');
    tmp_b=uint8_t(stoi(tmp));
    lineColor_.setRGB(tmp_r, tmp_g, tmp_b);
    getline(input, tmp, '\n');
    tmp_r=uint8_t(stoi(tmp));
    getline(input, tmp, '\n');
    tmp_g=uint8_t(stoi(tmp));
    getline(input, tmp, '\n');
    tmp_b=uint8_t(stoi(tmp));
    textColor_.setRGB(tmp_r, tmp_g, tmp_b);
    index_=Container::getCounterValue();
}

// getters
uint32_t Resistor::getType() {
    return type_;
}
string Resistor::getValue() {
    return value_;
}

// setters
bool Resistor::setValue(string _value) {
    value_ = _value;
    if (value_ == _value) return true;
    else return false;
}

// misc methods
string Resistor::parseSVGdefinition() {
    string parsed = "";
    uint8_t textSize = 15;

    //main body
    parsed += "<rect x='";
    parsed += to_string(x_);
    parsed += "' y='";
    parsed += to_string(y_);

    parsed += "' width='";
    parsed += to_string(50);
    parsed += "' height='";
    parsed += to_string(20);
    parsed += "' style=\"fill:";
    parsed += fillColor_.returnStringValue();
    parsed += ";stroke:";
    parsed += lineColor_.returnStringValue();
    parsed += ";stroke-width:";
    parsed += to_string(lineWidth_);
    parsed += "\" />\n";
    //end of main body
    //side lines
    parsed += "<line x1='";
    parsed += to_string(x_ - 25);
    parsed += "' y1='";
    parsed += to_string(y_ + 10);
    parsed += "' x2='";
    parsed += to_string(x_);
    parsed += "' y2='";
    parsed += to_string(y_ + 10);
    parsed += "' style=\"stroke:";
    parsed += lineColor_.returnStringValue();
    parsed += ";stroke-width:";
    parsed += to_string(lineWidth_);
    parsed += "\" />\n";
    parsed += "<line x1='";
    parsed += to_string(x_ + 50);
    parsed += "' y1='";
    parsed += to_string(y_ + 10);
    parsed += "' x2='";
    parsed += to_string(x_ + 75);
    parsed += "' y2='";
    parsed += to_string(y_ + 10);
    parsed += "' style=\"stroke:";
    parsed += lineColor_.returnStringValue();
    parsed += ";stroke-width:";
    parsed += to_string(lineWidth_);
    parsed += "\" />\n";
    //end of side lines
    //end of side lines
    //designator
    parsed += "<text x='";
    parsed += to_string(x_+50+lineWidth_);
    parsed += "' y='";
    parsed += to_string(y_);
    parsed += "' font-size='";
    parsed += to_string(textSize);
    parsed += "' fill='";
    parsed += textColor_.returnStringValue();
    parsed += "'>";
    parsed += designator_;
    parsed += "</text>\n";
    //end of designator
    //value
    parsed += "<text x='";
    parsed += to_string(x_+50+lineWidth_);
    parsed += "' y='";
    parsed += to_string(y_+20+lineWidth_+0.2*textSize);
    parsed += "' font-size='";
    parsed += to_string(textSize);
    parsed += "' fill='";
    parsed += textColor_.returnStringValue();
    parsed += "'>";
    parsed += value_;
    parsed += "</text>\n";
    //end of value

    return parsed;
}
