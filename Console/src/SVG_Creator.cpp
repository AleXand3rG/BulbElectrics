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
    //Creating output directory
    string outputPath = "./Output/";
    Container::makeDir(outputPath);
    
    //Creating File
    ofstream file;
    outputPath += fileName_;
    file.open(outputPath, ios::out);
    if(file) {
        
        //Creating SVG: <svg viewBox="0 0 1000 500" xmlns="http://www.w3.org/2000/svg">
        file << "<svg viewBox=\"0 0 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\">\n\n";
        file << drawCoordinateSystem() << endl;
        if (canvas.getVector().size()!=0) {
            for (int i=0;i<canvas.getSize();i++)
                file << canvas.getVector()[i]->parseSVGdefinition() << endl;
        }        
        file << "</svg>";
        file.close();
        return true;
    }
    else {
        string err = "\nERROR: Could not create SVG file\n\n";
        throw err;
        return false;
    }
}
string SVG_Creator::drawCoordinateSystem() {
    string CS = "";
    CS += "<line x1='10' y1='10' x2='1000' y2='10' style='stroke:#000000;stroke-width:2' />\n"; //OX
    for (int i=100;i<1000;i+=100) {
        CS += "<line x1='";
        CS += to_string(i);
        CS += "' y1='";
        CS += to_string(10);
        CS += "' x2='";
        CS += to_string(i);
        CS += "' y2='";
        CS += to_string(15);
        CS += "' style='stroke:#000000;stroke-width:2' />\n";
        
        CS += "<text x='";
        CS += to_string(i+1);
        CS += "' y='";
        CS += to_string(25);
        CS += "' font-size='";
        CS += to_string(15);
        CS += "' fill='black'>";
        CS += to_string(i);
        CS += "</text>\n";
        
        CS += "<polyline points=\"";
        CS += to_string(990) + ',' + to_string(0);
        CS += " ";
        CS += to_string(1000) + ',' + to_string(10);
        CS += " ";
        CS += to_string(990) + ',' + to_string(20);
        CS += "\" ";
        CS += "style=\"fill:none;stroke:#000000";
        CS += ";stroke-width:";
        CS += to_string(1);
        CS += "\" />\n";
        
        CS += "<text x='";
        CS += to_string(960);
        CS += "' y='";
        CS += to_string(25);
        CS += "' font-size='";
        CS += to_string(15);
        CS += "' fill='black'>";
        CS += "OX";
        CS += "</text>\n";
    }
    
    CS += "<line x1='10' y1='10' x2='10' y2='1000' style='stroke:#000000;stroke-width:2' />\n\n"; //OY
    for (int i=100;i<1000;i+=100) {
        CS += "<line x1='";
        CS += to_string(10);
        CS += "' y1='";
        CS += to_string(i);
        CS += "' x2='";
        CS += to_string(15);
        CS += "' y2='";
        CS += to_string(i);
        CS += "' style='stroke:#000000;stroke-width:2' />\n";
        
        CS += "<text x='";
        CS += to_string(15);
        CS += "' y='";
        CS += to_string(i-1);
        CS += "' font-size='";
        CS += to_string(15);
        CS += "' fill='black'>";
        CS += to_string(i);
        CS += "</text>\n";
        
        CS += "<polyline points=\"";
        CS += to_string(0) + ',' + to_string(990);
        CS += " ";
        CS += to_string(10) + ',' + to_string(1000);
        CS += " ";
        CS += to_string(20) + ',' + to_string(990);
        CS += "\" ";
        CS += "style=\"fill:none;stroke:#000000";
        CS += ";stroke-width:";
        CS += to_string(1);
        CS += "\" />\n";
        
        CS += "<text x='";
        CS += to_string(15);
        CS += "' y='";
        CS += to_string(985);
        CS += "' font-size='";
        CS += to_string(15);
        CS += "' fill='black'>";
        CS += "OY";
        CS += "</text>\n";
    }
    return CS;
}
