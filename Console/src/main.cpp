//
//  main.cpp
//  proe-19l-2
//
//  Created by Aleksander Grzybowski & Piotr Daniel on 18/04/19.
//  Copyright © 2019 Aleksander Grzybowski & Piotr Daniel. All rights reserved.
//

#include "Application.hpp"
#include "Container.hpp"
#include "Element.hpp"
#include "Bulb.hpp"
#include "SmartBulb.hpp"
#include "Resistor.hpp"
#include "Varistor.hpp"
#include "Color.hpp"
#include "SVG_Creator.hpp"

int main() {
    Application* App = Application::getInstance();
    App->splash();
    App->menu();
    return 0;
}
