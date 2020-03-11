//
//  Bulb.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "Bulb.hpp"
#include "Container.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define ON true
#define OFF false

using namespace std;

//Constructors:
uint32_t Bulb::type_=BULB;
Bulb::Bulb(uint16_t x,uint16_t y) {
    index_ = Container::getCounterValue();
    designator_ = "Default Bulb";
    x_ = x;
    y_ = y;
    lineWidth_ = 2;
    radius_ = 20;
    wattage_ = 10;
    fillColor_.setColorByName("White");
    lineColor_.setColorByName("Black");
    textColor_.setColorByName("Black");
    state_ = ON;
}
Bulb::Bulb(uint32_t i,string d,uint16_t x,uint16_t y,uint16_t lw,uint16_t r,uint16_t p,Color FC,Color LC,Color TC,bool state) {
    index_ = i;
    designator_ = d;
    x_ = x;
    y_ = y;
    lineWidth_ = lw;
    radius_ = r;
    wattage_ = p;
    fillColor_ = FC;
    lineColor_ = LC;
    textColor_ = TC;
    state_ = state;
}

//iostream
void Bulb::printInfo(ostream& os) const {
    string ONOFF="OFF";
    if (state_) ONOFF="ON";
    
    os << index_+1 << ". ";
    os << "Designator: " << designator_ << endl;
    os << "Coordinate x: " << x_ << endl;
    os << "Coordinate y: " << y_ << endl;
    os << "Line Width: " << lineWidth_ << endl;
    os << "Radius: " << radius_ << endl;
    os << "Wattage: " << wattage_ << 'W' << endl;
    os << "Fill Color: " << fillColor_.returnStringValue() << endl;
    os << "Line Color: " << lineColor_.returnStringValue() << endl;
    os << "Text Color: " << textColor_.returnStringValue() << endl;
    os << "State: " << ONOFF << endl;
    os << endl;
}
void Bulb::save(ofstream& output) {
    uint16_t ONOFF=0;
    if (this->getState()) ONOFF=1;

    output<<type_<<endl;
    output<<designator_<<endl;
    output<<x_<<endl;
    output<<y_<<endl;
    output<<lineWidth_<<endl;
    output<<radius_<<endl;
    output<<wattage_<<endl;
    output<<to_string(fillColor_.returnR())<<endl;
    output<<to_string(fillColor_.returnG())<<endl;
    output<<to_string(fillColor_.returnB())<<endl;
    output<<to_string(lineColor_.returnR())<<endl;
    output<<to_string(lineColor_.returnG())<<endl;
    output<<to_string(lineColor_.returnB())<<endl;
    output<<to_string(textColor_.returnR())<<endl;
    output<<to_string(textColor_.returnG())<<endl;
    output<<to_string(textColor_.returnB())<<endl;
    output<<ONOFF<<endl;
}
void Bulb::read(ifstream& input) {
    string tmp;
    uint8_t tmp_state=0;
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
    getline(input, tmp, '\n');
    radius_=uint16_t(stoi(tmp));
    getline(input, tmp, '\n');
    wattage_=uint16_t(stoi(tmp));
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
    getline(input, tmp, '\n');
    tmp_state=uint8_t(stoi(tmp));
    if (tmp_state) state_=ON; else state_=OFF;
    index_=Container::getCounterValue();
}

//getters
uint32_t Bulb::getType() {
    return type_;
}
uint16_t Bulb::getRadius() {
    return radius_;
}
uint16_t Bulb::getWattage() {
    return wattage_;
}
bool Bulb::getState() {
    return state_;
}

// setters
bool Bulb::setRadius(uint16_t _value) {
    radius_ = _value;
    if (radius_ == _value) return true;
    else return false;
}
bool Bulb::setWattage(uint16_t _value) {
    wattage_ = _value;
    if (wattage_ == _value) return true;
    else return false;
}
bool Bulb::setState(bool _value) {
    if (_value==ON || _value==OFF) state_ = _value;
    if (state_ == _value) return true;
    else return false;
}

// misc methods
string Bulb::parseSVGdefinition() {
    string parsed = "";
    uint8_t textSize = 15;
    if (radius_>500) textSize = 40;
    else if (radius_<=500 && radius_>200) textSize = 30;
    else if (radius_<=200 && radius_>100) textSize = 25;
    else if (radius_<=100 && radius_>50) textSize = 20;

    //main body
    parsed += "<circle cx='";
    parsed += to_string(x_);
    parsed += "' cy='";
    parsed += to_string(y_);
    parsed += "' r='";
    parsed += to_string(radius_);
    parsed += "' stroke='";
    parsed += lineColor_.returnStringValue();
    parsed += "' stroke-width='";
    parsed += to_string(lineWidth_);
    parsed += "' ";
    if (state_) {
        parsed += "fill='";
        parsed += fillColor_.returnStringValue();
        parsed += "' />\n";
    }
    else {
        parsed += "fill='";
        parsed += "#FFFFFF";
        parsed += "' />\n";
    }
    //X
    parsed += "<polyline points=\"";
    parsed += to_string(x_-radius_/sqrt(2)) + ',' + to_string(y_-radius_/sqrt(2));
    parsed += " ";
    parsed += to_string(x_+radius_/sqrt(2)) + ',' + to_string(y_+radius_/sqrt(2));
    parsed += " ";
    parsed += to_string(x_) + ',' + to_string(y_);
    parsed += " ";
    parsed += to_string(x_+radius_/sqrt(2)) + ',' + to_string(y_-radius_/sqrt(2));
    parsed += " ";
    parsed += to_string(x_-radius_/sqrt(2)) + ' ' + to_string(y_+radius_/sqrt(2));
    parsed += "\" ";
    parsed += "style=\"fill:none;stroke:";
    if (state_==ON)
        parsed += "#000000";
    else
        parsed += lineColor_.returnStringValue();
    parsed += ";stroke-width:";
    parsed += to_string(lineWidth_);
    parsed += "\" />\n";
    //end of X
    //end of main body
    //left side line
    parsed += "<line x1='";
    parsed += to_string(x_-2*radius_);
    parsed += "' y1='";
    parsed += to_string(y_);
    parsed += "' x2='";
    parsed += to_string(x_-radius_);
    parsed += "' y2='";
    parsed += to_string(y_);
    parsed += "' style ='stroke:";
    parsed += lineColor_.returnStringValue();
    parsed += ";stroke-width:";
    parsed += to_string(lineWidth_);
    parsed += "'/>\n";
    //end of left side line
    //right side line
    parsed += "<line x1='";
    parsed += to_string(x_+radius_);
    parsed += "' y1='";
    parsed += to_string(y_);
    parsed += "' x2='";
    parsed += to_string(x_+2*radius_);
    parsed += "' y2='";
    parsed += to_string(y_);
    parsed += "' style ='stroke:";
    parsed += lineColor_.returnStringValue();
    parsed += ";stroke-width:";
    parsed += to_string(lineWidth_);
    parsed += "'/>\n";
    //end of right side line
    //designator
    parsed += "<text x='";
    parsed += to_string(x_+radius_+lineWidth_);
    parsed += "' y='";
    parsed += to_string(y_-lineWidth_-0.5*textSize);
    parsed += "' font-size='";
    parsed += to_string(textSize);
    parsed += "' fill='";
    parsed += textColor_.returnStringValue();
    parsed += "'>";
    parsed += designator_;
    parsed += "</text>\n";
    //end of designator
    //wattage
    parsed += "<text x='";
    parsed += to_string(x_+radius_+lineWidth_);
    parsed += "' y='";
    parsed += to_string(y_+lineWidth_+textSize);
    parsed += "' font-size='";
    parsed += to_string(textSize);
    parsed += "' fill='";
    parsed += textColor_.returnStringValue();
    parsed += "'>";
    parsed += to_string(wattage_);
    parsed += "W</text>\n";
    //end of wattage

    return parsed;
}

/*
 SVG Bulb template:

 left line:  <line x1='100' y1='100' x2='150' y2='100' style='stroke:rgb(255,0,0);stroke-width:2' />
 bulb:       <circle cx='200' cy='100' r='50' stroke='green' stroke-width='2' fill='white' />
 X:          <polyline points="165,65 235,135 200,100 235,65 165,135"
 style="fill:none;stroke:rgb(255,0,0);stroke-width:3" />
 right line: <line x1='250' y1='100' x2='300' y2='100' style='stroke:rgb(255,0,0);stroke-width:2' />
 designator: <text x='175' y='40' fill='red'>Żarówa</text>
 wattage:    <text x='181' y='170' fill='red'>100W</text>

 */
