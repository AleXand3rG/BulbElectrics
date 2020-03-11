//
//  Application.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "Application.hpp"
#include "SVG_Creator.hpp"

#include <cmath>

using namespace std;

//Constructors
Application* Application::AppInstance_ = nullptr;

Application::Application(){}

Application* Application::getInstance() {
    if (AppInstance_==0) AppInstance_ = new Application();
    return AppInstance_;
}

//UI
void Application::splash() {
    clearScreen();
    cout << "Welcome!\n\n";
    showInfo(0);
    cout << "Created by Aleksander Grzybowski & Piotr Daniel.\n" << endl;

    cout << "Press ENTER to continue...";
    cin.clear();
    cin.ignore();
    clearScreen();
}
void Application::showInfo(int x) {
    if (x!=0) clearScreen(); if (x==0) cout << "\t";
    cout << "This Application lets you create and characterize objects of a circuit. Describe them and generate SVG file containing a sheme of what you have created. You can display the objects in browser or in SVG files editor. Give it a try and click \"New Element\" to create new object with its properties. Thank You for using this simple tool, have fun!\n" << endl;
}
void Application::menu () {
    int choice=-1;
    do {
        choice=-1;
        cout << "What would you like to do?\n"
                "1 - New Default Element\n"
                "2 - New Element\n"
                "3 - Edit Element\n"
                "4 - Delete Last Element\n"
                "5 - Select and Delete Element\n"
                "6 - Show Created Elements\n"
                "7 - Create SVG File\n"
                "8 - Save to File\n"
                "9 - Read from File\n\n"

                "10 - Delete All Elements\n"
                "11 - About\n"
                "0 - Exit\n";
        cin >> choice;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr<<"Numbers only\n";
            cin>>choice;
        }

        switch (choice) {
            case 1: newElement(true); break; //true if default element
            case 2: newElement(false); break;
            case 3: editElement(); break;
            case 4: clearScreen(); --canvas_; break;
            case 5: deleteSelectedElement(); break;
            case 6: displayContainer(); break;
            case 7: prepareSVG(); break;
            case 8: {
                cout << "Saving to file" << endl;
                string outputPath = editPath();
                try {if (canvas_.saveToFile(outputPath)) cout <<"Saved"<<endl;}
                catch(string err){cerr<<err;}
                break;
            }
            case 9: {
                try {
                    canvas_.readFromFile(editInputStream());
                }
                catch(string err) {cout<<err;} break;}
            case 10: canvas_.getVector().clear(); Container::resetCounter(); clearScreen(); break;
            case 11: showInfo(1); break;
            case 0: exit(-1); break;
            default: cerr<<"No such option. Try again\n"; break;
        }
    } while (choice!=0);
}

void Application::newElement(bool isDefault) {
    uint16_t x,y;
    int type=-1;
    do {
        type=-1;

        cout << "Element of which type would you like to create?\n"
        "1 - Bulb\n"
        "2 - Resistor\n"
        "3 - SmartBulb\n"
        "4 - Varistor\n"
        "0 - Back\n";
        cin>>type;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr<<"Numbers only\n";
            cin>>type;
        }

        switch (type) {
            case Element::BULB:
                if (isDefault) {
                    setPosition(x,y);
                    Element *newDefault = new Bulb(x,y);
                    canvas_ + newDefault;
                }
                else canvas_ + newElement(Element::BULB); break;
            case Element::RESISTOR:
                if (isDefault) {
                    setPosition(x,y);
                    Element *newDefault = new Resistor(x,y);
                    canvas_ + newDefault;
                }
                else canvas_ + newElement(Element::RESISTOR); break;
            case Element::SMARTBULB:
                if (isDefault) {
                    setPosition(x,y);
                    Element *newDefault = new SmartBulb(x,y);
                    canvas_ + newDefault;
                }
                else canvas_ + newElement(Element::SMARTBULB); break;
            case Element::VARISTOR:
                if (isDefault) {
                    setPosition(x,y);
                    Element *newDefault = new Varistor(x,y);
                    canvas_ + newDefault;
                }
                else canvas_ + newElement(Element::VARISTOR); break;
            case 0: type=0; clearScreen(); break;
            default: cerr<<"No such option. Try again\n"; break;
        }
     } while (type!=0);
}
void Application::setPosition(uint16_t &x, uint16_t &y) {
    cout << "Enter x position: ";
    cin>>x;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive only\n";
        cin>>x;
    }
    cout << "Enter y position: ";
    cin>>y;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive only\n";
        cin>>y;
    }
}
Element* Application::newElement(int type) {
    Element* newElement = nullptr;

    uint32_t newIndex = Container::getCounterValue();
    string newD = editDesignator();
    uint16_t newX = editX();
    uint16_t newY = editY();
    uint16_t newLW = editLineWidth();
    Color newFC = editColor();
    Color newLC = editColor();
    Color newTC = editColor();

    if (type==Element::BULB || type==Element::SMARTBULB) {
        uint16_t newR = editRadius();
        uint16_t newW = editWattage();
        bool newS = editState();
        if (type==Element::BULB)
            newElement = new Bulb (newIndex,newD,newX,newY,newLW,newR,newW,newFC,newLC,newTC,newS);
        else {
            uint8_t newI = editIntensity();
            newElement = new SmartBulb (newIndex,newD,newX,newY,newLW,newR,newW,newFC,newLC,newTC,newS,newI);
        }
    }
    else if (type==Element::RESISTOR || type==Element::VARISTOR) {
        string newValue = editValue();
        if (type==Element::RESISTOR)
            newElement = new Resistor (newIndex,newD,newX,newY,newLW,newValue,newFC,newLC,newTC);
        else {
            //nowe atrbuty
            //newElement = new Varistor (****);
        }
    }
    return newElement;
}
void Application::editElement() {
    clearScreen();
    if (!canvas_.isEmpty()) {
        uint32_t which;
        cout << "Which element do you want to edit?" << endl;
        cin >> which;
        while (cin.fail() || which==0) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr<<"Positive only\n";
            cin>>which;
        } which--;

        if (canvas_.isElement(which)) {
            if (canvas_.getElementPtr(which)->getType()==Element::BULB || canvas_.getElementPtr(which)->getType()==Element::SMARTBULB) {
                int atribute=-1;
                do {
                    atribute=-1;
                    cout << canvas_.getElementPtr(which);

                    cout << "What would you like to change?\n"
                    "1 - Change designator\n"
                    "2 - Change x coordinate\n"
                    "3 - Change y coordinate\n"
                    "4 - Change line width\n"
                    "5 - Change radius\n"
                    "6 - Change wattage\n"
                    "7 - Change light color\n"
                    "8 - Change line color\n"
                    "9 - Change text color\n"
                    "10 - Change State\n\n";

                    if (canvas_.getElementPtr(which)->getType()==Element::SMARTBULB) {
                        cout << "11 - Change intensity\n";
                    }
                    cout << "0 - Back\n";

                    cin>>atribute;
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cerr<<"Numbers only\n";
                        cin>>atribute;
                    }

                    auto it = canvas_.getElementPtr(which);
                    switch (atribute) {
                        case 1: it->setDesignator(editDesignator()); break;
                        case 2: it->setX(editX()); break;
                        case 3: it->setY(editY()); break;
                        case 4: it->setLineWidth(editLineWidth()); break;
                        case 5: dynamic_cast<Bulb*>(it)->setRadius(editRadius()); break;
                        case 6: dynamic_cast<Bulb*>(it)->setWattage(editWattage()); break;
                        case 7: it->setFillColor(editColor()); break;
                        case 8: it->setLineColor(editColor()); break;
                        case 9: it->setTextColor(editColor()); break;
                        case 10: dynamic_cast<Bulb*>(it)->setState(editState()); break;
                        case 11: {if (it->getType()==Element::SMARTBULB)
                            dynamic_cast<SmartBulb*>(it)->setIntensity(editLineWidth());
                            else cerr<<"No such option. Try again\n";;
                            break;
                        }
                        case 0: atribute=0; break;
                        default: cerr<<"No such option. Try again\n"; break;
                    }
                    clearScreen();
                } while (atribute!=0);
            }
            else if (canvas_.getElementPtr(which)->getType()==Element::RESISTOR ||
                     canvas_.getElementPtr(which)->getType()==Element::VARISTOR) {
                int atribute=-1;
                do {
                    atribute=-1;
                    cout << canvas_.getElementPtr(which);

                    cout << "What would you like to change?\n"
                    "1 - Change designator\n"
                    "2 - Change x coordinate\n"
                    "3 - Change y coordinate\n"
                    "4 - Change line width\n"
                    "5 - Change value\n"
                    "6 - Change fill color\n"
                    "7 - Change line color\n"
                    "8 - Change text color\n";

                    if (canvas_.getElementPtr(which)->getType()==Element::VARISTOR) {
                        cout << "9 - Change clamping voltage\n";
                    }
                    cout << "0 - Back\n";
                    cin>>atribute;
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cerr<<"Numbers only\n";
                        cin>>atribute;
                    }

                    auto it = canvas_.getElementPtr(which);
                    switch (atribute) {
                        case 1: it->setDesignator(editDesignator()); break;
                        case 2: it->setX(editX()); break;
                        case 3: it->setY(editY()); break;
                        case 4: it->setLineWidth(editLineWidth()); break;
                        case 5: dynamic_cast<Resistor*>(it)->setValue(editValue()); break;
                        case 6: it->setFillColor(editColor()); break;
                        case 7: it->setLineColor(editColor()); break;
                        case 8: it->setTextColor(editColor()); break;
                        case 9: {if (it->getType()==Element::VARISTOR)
                            dynamic_cast<Varistor*>(it)->setClampingVoltage(editClampingVoltage());
                            else cerr<<"No such option. Try again\n";
                            break;
                        }
                        case 0: atribute=0; break;
                        default: cerr<<"No such option. Try again\n"; break;
                    }
                    clearScreen();
                } while (atribute!=0);
            }
        }
    }
}
void Application::deleteSelectedElement() {
    uint32_t which;
    cout << "Which element do you want to delete?" << endl;
    cin >> which;
    while (cin.fail() || which<=0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive only\n";
        cin>>which;
    } which--;
    canvas_-which;
    clearScreen();
}
void Application::displayContainer () {
    clearScreen();
    cout << "Your Created Elements: " << endl;
    if (!canvas_.isEmpty()) {
        for (int i=0;i<canvas_.getSize();i++) {
            cout << canvas_.getElementPtr(i);
        }
    }
    else cerr << "Container is empty\n";
    cout << endl;
}
void Application::prepareSVG() {
    string fname;
    cout << "Preparing SVG file" << endl;
    cout << "Enter file name (without extension): ";
    cin >> fname;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Invalid file name, try again\n";
        cin>>fname;
    } fname+=".svg";
    SVG_Creator creator(fname);
    try {if (creator.createSVG(canvas_)) {clearScreen(); cout << "Saved" << endl;}}
    catch(string err) {cout << err;}
}
void Application::clearScreen() {
#ifdef WINDOWS_KEY_WORD
    system("cls");
#else
    system("clear");
#endif
}

//Element editors
string Application::editDesignator() {
    string newDesignator = "Default";
    cin.ignore();
    cout << "Type new name: ";
    getline(cin, newDesignator, '\n');
    return newDesignator;
}
uint16_t Application::editX() {
    uint16_t newX = 100;
    cout << "Type new x coordinate: ";
    cin>>newX;
    while (cin.fail() || newX<0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive or 0 only\n";
        cin>>newX;
    } return newX;
}
uint16_t Application::editY() {
    uint16_t newY = 100;
    cout << "Type new y coordinate: ";
    cin>>newY;
    while (cin.fail() || newY<0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive or 0 only\n";
        cin>>newY;
    } return newY;
}
uint16_t Application::editLineWidth() {
    uint16_t newLineWidth = 2;
    cout << "Type new line width: ";
    cin>>newLineWidth;
    while (cin.fail() || newLineWidth<=0 || newLineWidth>10) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Integers from 1 to 10 only\n";
        cin>>newLineWidth;
    } return newLineWidth;
}

//Bulb editors
uint16_t Application::editRadius() {
    uint16_t newRadius = 50;
    cout << "Type new radius: ";
    cin>>newRadius;
    while (cin.fail() || newRadius<=0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive only\n";
        cin>>newRadius;
    } return newRadius;
}
uint16_t Application::editWattage() {
    uint16_t newWattage = 10;
    cout<<"Type new Wattage: ";
    cin>>newWattage;
    while (cin.fail() || newWattage<0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Positive or 0 only\n";
        cin>>newWattage;
    } return newWattage;
}
bool Application::editState() {
    int done=-2;
    int newState = false;
    cout<<"Type new state [1/0]: ";
    do {
        cin>>newState;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr<<"Wrong option! 0 or 1 only\n";
            cin>>newState;
        }
        switch (newState) {
            case 1: newState=1; done =-1; break;
            case 0: newState=0; done =-1; break;
            default: cerr<<"Wrong option! 0 or 1 only\n"; done=0; break;
        }
    } while (done!=-1);
    if (newState==1) return true;
    else return false;
}
//SmartBulb editors
uint8_t Application::editIntensity() {
    uint8_t newIntensity = 50;
    cout << "Type new intensity: ";
    cin >> newIntensity;
    while (cin.fail() || newIntensity>100 || newIntensity<0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 100 numbers only\n";
        cin>>newIntensity;
    }
    return newIntensity;
}

//Resistor editors
string Application::editValue() {
    string newValue = "?value?";
    do {
        cout << "Type new value: ";
        cin >> newValue;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr<<"Letters only\n";
            cin>>newValue;
        }
        if (newValue.length()>16) cerr<<"Too many characters\n";
    } while(newValue.length()>16);
    return newValue;
}
//Varistor editors
float Application::editClampingVoltage() {
    float newClampingVoltage = 50;
    cout << "Type new clamping voltage: ";
    cin>>newClampingVoltage;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin>>newClampingVoltage;
    } return newClampingVoltage;
}


//Color Editor
Color Application::editColor() {
    Color newColor;
    int representation=-1;
    do {
        representation=-1;
        cout << "Which type of color representation would you like to use?\n"
        "1 - HSV\n"
        "2 - CMYK\n"
        "3 - RGB\n"
        "4 - by name\n";
        cin>>representation;
        while (cin.fail() || representation<=0) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr<<"Positive only\n";
            cin>>representation;
        }

        switch (representation) {
            case 1: editHSV(newColor); representation=-1; break;
            case 2: editCMYK(newColor); representation=-1; break;
            case 3: editRGB(newColor); representation=-1; break;
            case 4: editByName(newColor); representation=-1; break;
            default: cerr<<"No such option. Try again\n"; break;
        }
    } while (representation!=-1);
    return newColor;
}

//HSV
void Application::editHSV(Color& newColor) {
    newColor.setHSV(HSVeditHue(), HSVeditSaturation(), HSVeditValue());
}
uint32_t Application::HSVeditHue() {
    uint32_t newHue;
    cout << "Enter hue (range [0-360]): ";  cin>>newHue;
    while (cin.fail()) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 360 numbers only\n";
        cin>>newHue;
    }
    return newHue;
}
float Application::HSVeditSaturation() {
    float newSaturation;
    cout << "Enter saturation (range [0-1]): "; cin>>newSaturation;
    while (cin.fail()) {
        cin.clear(); cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 1 only\n";
        cin>>newSaturation;
    }
    return newSaturation;
}
float Application::HSVeditValue() {
    float newValue;
    cout << "Enter value (range [0-1]): "; cin>>newValue;
    while (cin.fail()) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 1 only\n";
        cin>>newValue;
    }
    return newValue;
}
//CMYK
void Application::editCMYK(Color& newColor) {
    newColor.setCMYK(CMYKeditCyan(), CMYKeditMagenta(), CMYKeditYellow(), CMYKeditBlack());
}
float Application::CMYKeditCyan() {
    float newCyan;
    cout << "Enter cyan value (range [0-1]): "; cin>>newCyan;
    while (cin.fail()) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 1 only\n";
        cin>>newCyan;
    }
    return newCyan;
}
float Application::CMYKeditMagenta() {
    float newMagenta;
    cout << "Enter magenta value (range [0-1]): "; cin>>newMagenta;
    while (cin.fail()) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 1 only\n";
        cin>>newMagenta;
    }
    return newMagenta;
}
float Application::CMYKeditYellow() {
    float newYellow;
    cout << "Enter yellow value (range [0-1]): "; cin>>newYellow;
    while (cin.fail()) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 1 only\n";
        cin>>newYellow;
    }
    return newYellow;
}
float Application::CMYKeditBlack() {
    float newBlack;
    cout << "Enter black value (range [0-1]): ";  cin>>newBlack;
    while (cin.fail()) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 1 only\n";
        cin>>newBlack;
    }
    return newBlack;
}
//RGB
void Application::editRGB(Color& newColor) {
    newColor.setRGB(RGBeditRed(), RGBeditGreen(), RGBeditBlue());
}
uint32_t Application::RGBeditRed() {
    uint32_t newRed;
    cout << "Enter red value (range [0-255]): "; cin>>newRed;
    while (cin.fail()||(newRed>255||newRed<0)) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 255 numbers only\n";
        cin>>newRed;
    }
    return newRed;
}
uint32_t Application::RGBeditGreen() {
    int newGreen;
    cout << "Enter green value (range [0-255]): "; cin>>newGreen;
    while (cin.fail()||(newGreen>255||newGreen<0)) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 255 numbers only\n";
        cin>>newGreen;
    }
    return newGreen;
}
uint32_t Application::RGBeditBlue() {
    uint32_t newBlue;
    cout << "Enter blue value (range [0-255]): "; cin>>newBlue;
    while (cin.fail()||(newBlue>255||newBlue<0)) {
        cin.clear();cin.ignore(INT_MAX, '\n');
        cerr<<"Numbers from 0 to 255 numbers only\n";
        cin>>newBlue;
    }
    return newBlue;
}
//byName
void Application::editByName(Color& newColor) {
    string newName;
    int done=-2;
    do {
        done=-2;
        cout << "(HTML 3.0 specification:\n"
        "Black, White, Gray, Silver,\n"
        "Purple, Green, Navy, Red,\n"
        "Maroon, Olive, Aqua, Lime,\n"
        "Yellow,  Blue, Teal, Fuchsia)\n"
        "Enter color name: ";
        string newName;
        cin>>newName;
        while (cin.fail()) {
            cin.clear();
            cin>>newName;
        } cout<<endl;
        if (newColor.setColorByName(newName)) done=-1;
        else cerr<<"Wrong color name\n";
    } while (done!=-1);
}

//fstream
string Application::editPath() {
    string path = "./.resources/";
    Container::makeDir(path);
    string fname;
    cout << "Enter file name (without extension): ";
    cin >> fname;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr<<"Invalid file name, try again\n";
        cin>>fname;
    }
    fname+=".data";
    path += fname;
    return path;
}
string Application::editInputStream() {
    cout << "Reading from file" << endl;
    cout << "Make sure that your file is in \".resources\" directory." << endl;
    string inputPath = editPath();
    return inputPath;
}
