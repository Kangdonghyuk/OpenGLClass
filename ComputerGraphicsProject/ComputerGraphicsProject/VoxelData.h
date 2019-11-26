//
//  VoxelData.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 25..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef VoxelData_hpp
#define VoxelData_hpp

#include <cmath>

typedef struct POSITION {
    float x, y, z;
    float Size() {
        return sqrtf(x*x + z*z);
    }
    POSITION Nomalize() {
        POSITION _nor;
        float _size = Size();
        _nor.x = x / _size;
        _nor.z = z / _size;
        return _nor;
    }
}Position;

static Position PositionZero = {0, 0, 0};

typedef struct COLOR {
    float r, g, b, a;
}Color;

const Position voxelPos[8] = {
    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f}
};

enum VOXELFACE {
    FRONT,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    BEHIND
};

const int voxelIndex[6][4] = {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {1, 0, 4, 5},
    {4, 0, 3, 7},
    {1, 5, 6, 2},
    {5, 4, 7, 6}
};

const Color voxelColor[6] {
    {1, 0, 0, 1},
    {0, 1, 0, 1},
    {0, 0, 1, 1},
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {0, 1, 1, 1}
};

#endif /* VoxelData_hpp */
