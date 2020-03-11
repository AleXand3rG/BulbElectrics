//
//  Application.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include "Container.hpp"
#include "Element.hpp"

#include <iostream>
#include <string>

class Application {
private:
    static Application* AppInstance_;
    Container canvas_;
    
protected:
    Application();
public:
    static Application* getInstance();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    std::string editInputStream();
    std::string editPath();

    //UI:
    void splash();
    void showInfo(int);
    void menu();

    void newElement(bool);
    void setPosition(uint16_t&,uint16_t&);
    Element* newElement(int);

    void editElement();
    void deleteSelectedElement();
    void displayContainer();
    void prepareSVG();
    void clearScreen();

    //Element editors
    //All
    std::string editDesignator();
    uint16_t editX();
    uint16_t editY();
    uint16_t editLineWidth();
    Color editColor();
    //Bulb
    uint16_t editRadius();
    uint16_t editWattage();
    bool editState();
    //Resistor
    std::string editValue();
    //SmartBulb
    uint8_t editIntensity();
    //Varistor
    float editClampingVoltage();
    
    //HSV
    void editHSV(Color&);
    uint32_t HSVeditHue();
    float HSVeditSaturation();
    float HSVeditValue();
    //CMYK
    void editCMYK(Color&);
    float CMYKeditCyan();
    float CMYKeditMagenta();
    float CMYKeditYellow();
    float CMYKeditBlack();
    //RGB
    void editRGB(Color&);
    uint32_t RGBeditRed();
    uint32_t RGBeditGreen();
    uint32_t RGBeditBlue();
    //byName
    void editByName(Color&);
};

#endif /* Application_hpp */
