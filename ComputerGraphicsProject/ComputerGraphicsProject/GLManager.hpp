//
//  GLManager.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

/*
 OpenGL 관리 클래스
 */

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

//함수포인터 타입 정의
typedef void (*FuncPtr)(void);

//GL비트맵 구조체
typedef struct GLTEX {
    Bitmap * bit;
    unsigned int objIndex;
}GLTex;

class GLManager {
public:
    static std::vector<FuncPtr> funcList; // 콜백함수 배열
    static std::vector<GLTex*> textureList; // 비트맵 배열
public:
    static void Init(int * argc, char * argv[]);
    static void Rendering();
    static void Loop();
    static void LightInit();
    static void DrawUI();     // UI 그려주기
    static void DrawVoxel(int x, int y, int z, int type); // 블럭 그져루기
    static void RemoveBlock(); // 블럭 지우기
    static void AddBlock(); // 블럭 추가
public:
    static void CBIdle(); // 기본 콜백 함수
public:
    static void AddCBFunc(FuncPtr ptr); // 콜백함수 추가
    static void LoadGLTextures(); // GL비트맵 로드
};

extern GLManager glMNG;

#endif /* GLManager_hpp */
