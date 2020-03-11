//
//  SVG_Creator.hpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#ifndef SVG_Creator_hpp
#define SVG_Creator_hpp

#include "Element.hpp"
#include "Container.hpp"

#include <string>
#include <vector>

class SVG_Creator {
    std::string fileName_;
    
public:
    SVG_Creator(std::string);
    
    std::string drawGrid(int,int);
    bool createSVG(Container&);
    std::string drawCoordinateSystem();
};

#endif /* SVG_Creator_hpp */
