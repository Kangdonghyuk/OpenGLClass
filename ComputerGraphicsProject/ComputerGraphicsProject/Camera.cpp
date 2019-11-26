//
//  Camera.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "Camera.hpp"
#include <cmath>

void Camera::Translate(Position _pos) {
    float _rad = acosf(_pos.Nomalize().z);
    Position _dir = {sinf(_rad), 0, cosf(_rad)};
    
    position.x += _dir.x;
    position.z -= _dir.z;
}
void Camera::Rotate(Position _rot) {
    direction.x = sinf(direction.x + _rot.x);
    direction.y = cosf(direction.y + _rot.y);
}
