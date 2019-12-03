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
    float AllSize() {
        return sqrtf(x*x + y*y + z*z);
    }
    POSITION Normalize() {
        POSITION _nor;
        float _size = Size();
        _nor.x = x / _size;
        _nor.z = z / _size;
        return _nor;
    }
    POSITION AllNormalize() {
        POSITION _nor;
        float _size = AllSize();
        _nor.x = x / _size;
        _nor.y = y / _size;
        _nor.z = z / _size;
        return _nor;
    }
}Position;

static Position PositionZero = {0, 0, 0};

typedef struct COLOR {
    float r, g, b, a;
}Color;

const Position voxelPos[8] = {
    {0, -0.5f, 0},
    {1, -0.5f, 0},
    {1, 0.5f, 0},
    {0, 0.5f, 0},
    {0, -0.5f, -1},
    {1, -0.5f, -1},
    {1, 0.5f, -1},
    {0, 0.5f, -1}
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

const int voxelTexture[8][6] = {
    {0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2},
    {4, 4, 4, 4, 4, 4},
    {7, 7, 7, 7, 7, 7},
    {3, 146, 2, 3, 3, 3},
    {2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1}
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
