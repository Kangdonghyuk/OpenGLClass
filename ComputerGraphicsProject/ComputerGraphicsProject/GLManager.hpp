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

#include "BitmapMNG.hpp"
#include "VoxelData.h"
#include "Camera.hpp"
#include "WorldData.hpp"
#include "Input.hpp"
//#include "PerlinNoise.hpp"

typedef void (*FuncPtr)(void);

typedef struct GLTEX {
    Bitmap * bit;
    unsigned int objIndex;
}GLTex;

class GLManager {
public:
    static std::vector<FuncPtr> funcList;
    static std::vector<GLTex*> textureList;
public:
    static void Init(int * argc, char * argv[]);
    static void Rendering();
    static void Loop();
    static void LightInit();
    static void DrawUI();
    static void DrawVoxel(int x, int y, int z, int type);
    static void RemoveBlock();
    static void AddBlock();
public:
    static void CBIdle();
public:
    static void AddCBFunc(FuncPtr ptr);
    static void LoadGLTextures();
};

extern GLManager glMNG;

#endif /* GLManager_hpp */
