//
//  Camera.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "Camera.hpp"
#include <cmath>

Camera::Camera() {
    position = PositionZero;
    position.y = 15;
    
    direction = PositionZero;
    
    look = PositionZero;
    look.z = 1;
}

void Camera::Translate(Position _pos, bool _isVertical) {
    _pos = _pos.Nomalize();
    if(_isVertical) {
        position.x += look.x * -_pos.z;
        position.z += look.z * _pos.z;
        
        position.x += look.z * _pos.x;
    }
    else {
        position.x += look.z * _pos.x;
        position.z += look.x * _pos.x;
    }
}
void Camera::Rotate(Position _rot) {
    direction.x += _rot.y;
    direction.z += _rot.y;
    
    look.x = sinf(direction.x);
    look.z = cosf(direction.z);
}
