//
//  GLManager.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef GLManager_hpp
#define GLManager_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <cmath>

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "VoxelData.h"
#include "Camera.hpp"

typedef void (*FuncPtr)(void);

class GLManager {
public:
    static std::vector<FuncPtr> funcList;
public:
    static void Init(int * argc, char * argv[]);
    static void Rendering();
    static void Loop();
public:
    static void CBIdle();
    static void CBKeyboard(unsigned char key, int x, int y);
public:
    static void AddCBFunc(FuncPtr ptr);
};

extern GLManager glMNG;

#endif /* GLManager_hpp */
