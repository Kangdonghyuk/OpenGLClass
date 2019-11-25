//
//  main.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "GLManager.hpp"

GLManager glMNG;

float px = 0.5, py = 0;

void PPR(void) {
    int _x = rand() % 20 - 10;
    int _y = rand() % 20 - 10;
    
    glMNG.AddVertex({(float)_x, (float)_y});
}


int main(int argc, char * argv[]) {
    glMNG.Init(&argc, argv);
    
    glMNG.AddCBFunc(PPR);
    
    glMNG.Loop();
    
    return 0;
}
