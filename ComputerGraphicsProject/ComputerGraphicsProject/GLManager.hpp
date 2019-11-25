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

#endif /* GLManager_hpp */

typedef struct VERTEX {
    float x, y;
}Vertex;

typedef void (*FuncPtr)(void);

class GLManager {
public:
    static std::vector<Vertex> vertexList;
    static std::vector<FuncPtr> funcList;
public:
    static void Init(int * argc, char * argv[]);
    static void Rendering();
    static void Loop();
public:
    static void CBIdle();
    static void CBKeyboard(unsigned char key, int x, int y);
public:
    static void AddVertex(Vertex newVertex);
    static void AddCBFunc(FuncPtr ptr);
};

extern GLManager glMNG;
