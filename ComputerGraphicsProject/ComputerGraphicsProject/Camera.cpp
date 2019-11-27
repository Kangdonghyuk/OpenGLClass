//
//  Camera.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "Camera.hpp"
#include "WorldData.hpp"
#include <cmath>

//World world;

Camera::Camera() {
    position = PositionZero;
    position.y = 15;
    position.x = 10;
    position.z = -10;
    
    direction = PositionZero;
    
    look = PositionZero;
    look.z = 1;
    
    velocity = PositionZero;
}

void Camera::Translate(Position _pos, bool _isVertical) {
    _pos = _pos.Nomalize();
    
    velocity.x = 0;
    velocity.z = 0;
    
    if(_isVertical) {
        velocity.x += look.x * -_pos.z;
        velocity.z += look.z * _pos.z;
        
        velocity.x += look.z * _pos.x;
    }
    else {
        velocity.x += look.z * _pos.x;
        velocity.z += look.x * _pos.x;
    }
    
    velocity.x  = velocity.x / 10.0f;
    velocity.z  = velocity.z / 10.0f;
    
    float _x = position.x + velocity.x;
    float _z = position.z + velocity.z;
    
    int _offsetX[2];
    int _offsetZ[2];
    
    _offsetX[0] = (int)_x;
    _offsetX[1] = (_x - (int)_x >= 0.5) ? _x+1 : _x-1;
    
    _offsetZ[0] = (int)_z;
    _offsetZ[1] = (_z - (int)_z >= 0.5) ? _z+1 : _z-1;

    
    if(world.ck[-_offsetZ[0]][_offsetX[0]][(int)position.y] == 1 ||
       world.ck[-_offsetZ[0]][_offsetX[1]][(int)position.y] == 1 ||
       world.ck[-_offsetZ[1]][_offsetX[0]][(int)position.y] == 1 ||
       world.ck[-_offsetZ[1]][_offsetX[1]][(int)position.y] == 1) {
        velocity.x = 0;
        velocity.z = 0;
    }
    
    position.x += velocity.x;
    position.z += velocity.z;
}
void Camera::Rotate(Position _rot) {
    direction.x += _rot.y;
    direction.z += _rot.y;
    direction.y += _rot.x;
    
    look.y = tanf(direction.y);
    look.x = sinf(direction.x);
    look.z = cosf(direction.z);
}
void Camera::Gravity() {
    float _x = position.x + velocity.x;
    float _z = position.z + velocity.z;
    
    int _offsetX[2];
    int _offsetZ[2];
    
    _offsetX[0] = (int)_x;
    _offsetX[1] = (_x - (int)_x >= 0.5) ? _x+1 : _x-1;
    
    _offsetZ[0] = (int)_z;
    _offsetZ[1] = (_z - (int)_z >= 0.5) ? _z+1 : _z-1;

    velocity.y -= 0.0098;
    
    if(velocity.y < 0 &&
       (world.ck[-_offsetZ[0]][_offsetX[0]][(int)position.y - 1] == 1 ||
        world.ck[-_offsetZ[0]][_offsetX[1]][(int)position.y - 1] == 1 ||
        world.ck[-_offsetZ[1]][_offsetX[0]][(int)position.y - 1] == 1 ||
        world.ck[-_offsetZ[1]][_offsetX[1]][(int)position.y - 1] == 1)) {
        velocity.y = 0;
    }
    
    position.y += velocity.y;
}
void Camera::Jump() {
    velocity.y = 0.2;
}
