//
//  main.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "GLManager.hpp"

GLManager glMNG;

int main(int argc, char * argv[]) {
    glMNG.Init(&argc, argv);
    
    glMNG.Loop();
    
    return 0;
}
