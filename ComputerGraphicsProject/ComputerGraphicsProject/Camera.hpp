//
//  Camera.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "VoxelData.h"

#define PI 3.141592
#define DEGREE_TO_RADIAN(value) value * (PI / 180)
#define RADIAN_TO_DEGREE(value) value * (180 / PI)

class Camera {
public:
    Position position;
    Position direction;
public:
    Camera() {
        position.x = 0;
        position.y = 0;
        position.z = 0;
        
        direction.x = 0;
        direction.y = 0;
        direction.z = 1;
    }
public:
    void Translate(Position pos);
    void Rotate(Position rot);
};

extern Camera cam;

#endif /* Camera_hpp */
