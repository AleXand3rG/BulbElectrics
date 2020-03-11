//
//  SVG_Creator.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "SVG_Creator.hpp"
#include "Element.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

//Constructor::
SVG_Creator::SVG_Creator(string fName) {fileName_ = fName;}

bool SVG_Creator::createSVG(Container& canvas) {
    //Creating File
    ofstream file;
    file.open(fileName_, ios::out);
    if(file) {

        //Creating SVG: <svg viewBox="0 0 1000 500" xmlns="http://www.w3.org/2000/svg">
        file << "<svg viewBox=\"0 0 2000 1000\" xmlns=\"http://www.w3.org/2000/svg\">\n\n";
        file << drawGrid(2000,1000);
        file << drawCoordinateSystem() << endl;
        if (canvas.getVector().size()!=0) {
            for (unsigned long i=0;i<canvas.getSize();i++)
                file << canvas.getVector()[i]->parseSVGdefinition() << endl;
        }
        file << "</svg>";
        file.close();
        return true;
    }
    else {
        string err = "\nERROR: Could not create SVG file\n\n";
        throw err;
    }
}

string SVG_Creator::drawGrid(int xsize, int ysize){
    string G = "";
    for(int i = 0; i<=xsize;i+=100){
        G += "<line x1='";
        G += to_string(i);
        G += "' y1='";
        G += to_string(0);
        G += "' x2='";
        G += to_string(i);
        G += "' y2='";
        G += to_string(ysize);
        G += "' style='stroke:#666666;stroke-width:2' />\n";
    }
    for(int i = 0; i<=ysize;i+=100){
        G += "<line x1='";
        G += to_string(0);
        G += "' y1='";
        G += to_string(i);
        G += "' x2='";
        G += to_string(xsize);
        G += "' y2='";
        G += to_string(i);
        G += "' style='stroke:#666666;stroke-width:2' />\n";
    }
    for(int i = 0; i<=xsize;i+=10){
        G += "<line x1='";
        G += to_string(i);
        G += "' y1='";
        G += to_string(0);
        G += "' x2='";
        G += to_string(i);
        G += "' y2='";
        G += to_string(ysize);
        G += "' style='stroke:#BBBBBB;stroke-width:1;stroke-dasharray=\"5,1\"' />\n";
    }
    for(int i = 0; i<=ysize;i+=10){
        G += "<line x1='";
        G += to_string(0);
        G += "' y1='";
        G += to_string(i);
        G += "' x2='";
        G += to_string(xsize);
        G += "' y2='";
        G += to_string(i);
        G += "' style='stroke:#BBBBBB;stroke-width:1;stroke-dasharray=\"5,1\"' />\n";
    }
    return G;

}

string SVG_Creator::drawCoordinateSystem() {
    string CS = "";
    for (int i=100;i<2000;i+=100) { //OX
        CS += "<text x='";
        CS += to_string(i-20);
        CS += "' y='";
        CS += to_string(20);
        CS += "' font-size='";
        CS += to_string(20);
        CS += "' fill='blue'>";
        CS += to_string(i);
        CS += "</text>\n";
    }

    for (int i=100;i<1000;i+=100) { //OY        
        CS += "<text x='";
        CS += to_string(5);
        CS += "' y='";
        CS += to_string(i+10);
        CS += "' font-size='";
        CS += to_string(20);
        CS += "' fill='blue'>";
        CS += to_string(i);
        CS += "</text>\n";
    }
    return CS;
}
