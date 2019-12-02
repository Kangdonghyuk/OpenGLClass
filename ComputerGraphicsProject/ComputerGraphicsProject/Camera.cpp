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
    position.x = 10;
    position.y = 15;
    position.z = -10;
    
    direction = PositionZero;
    
    look = PositionZero;
    look.z = 1;
    
    moveLook = PositionZero;
    moveLook.z = 1;
    
    velocity = PositionZero;
}

void Camera::Translate(Position _pos, bool _isVertical) {
    _pos = _pos.Normalize();
    
    velocity.x = 0;
    velocity.z = 0;
    
    if(_isVertical) {
        velocity.x += moveLook.x * -_pos.z;
        velocity.z += moveLook.z * _pos.z;
        
        //velocity.x += look.z * _pos.x;
    }
    else {
        velocity.x += moveLook.z * _pos.x;
        velocity.z += moveLook.x * _pos.x;
    }
    
    velocity.x  = velocity.x / 10.0f;
    velocity.z  = velocity.z / 10.0f;
    
    float _x = position.x + velocity.x;
    float _z = position.z + velocity.z;
    
    int _offsetX[2];
    int _offsetZ[2];
    
    _offsetX[0] = (int)_x;
    //_offsetX[1] = (_x - (int)_x >= 0.5) ? _x+1 : _x-1;
    _offsetX[1] = _offsetX[0];
    
    _offsetZ[0] = (int)_z;
    //_offsetZ[1] = (_z - (int)_z >= 0.5) ? _z+1 : _z-1;
    _offsetZ[1] = _offsetZ[0];
    
    int data[4];
    data[0] = world.GetData(-_offsetZ[0], _offsetX[0], (int)position.y);
    data[1] = world.GetData(-_offsetZ[0], _offsetX[1], (int)position.y);
    data[2] = world.GetData(-_offsetZ[1], _offsetX[0], (int)position.y);
    data[3] = world.GetData(-_offsetZ[1], _offsetX[1], (int)position.y);
    
    
    if(data[0] == 1 || data[1] == 1 || data[2] == 1 || data[3] == 1) {
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
    
    if(direction.y < -1.5 || direction.y > 1.5)
        direction.y -= _rot.x;
    
    moveLook.y = tanf(direction.y);
    moveLook.x = sinf(direction.x);
    moveLook.z = cosf(direction.z);
    
    look = moveLook.AllNormalize();
}
void Camera::Gravity() {
    float _x = position.x + velocity.x;
    float _z = position.z + velocity.z;
    
    int _offsetX[2];
    int _offsetZ[2];
    
    _offsetX[0] = (int)_x;
    //_offsetX[1] = (_x - (int)_x >= 0.5) ? _x+1 : _x-1;
    _offsetX[1] = _offsetX[0];
    
    _offsetZ[0] = (int)_z;
    //_offsetZ[1] = (_z - (int)_z >= 0.5) ? _z+1 : _z-1;
    _offsetZ[1] = _offsetZ[0];
    
    int data[4];
    data[0] = world.GetData(-_offsetZ[0], _offsetX[0], (int)position.y-1);
    data[1] = world.GetData(-_offsetZ[0], _offsetX[1], (int)position.y-1);
    data[2] = world.GetData(-_offsetZ[1], _offsetX[0], (int)position.y-1);
    data[3] = world.GetData(-_offsetZ[1], _offsetX[1], (int)position.y-1);
    
    velocity.y -= 0.0098;
    
    if(velocity.y < 0 &&
       (data[0] == 1 || data[1] == 1 || data[2] == 1 || data[3] == 1)) {
           velocity.y = 0;
       }
    
    data[0] = world.GetData(-_offsetZ[0], _offsetX[0], (int)position.y+1);
    data[1] = world.GetData(-_offsetZ[0], _offsetX[1], (int)position.y+1);
    data[2] = world.GetData(-_offsetZ[1], _offsetX[0], (int)position.y+1);
    data[3] = world.GetData(-_offsetZ[1], _offsetX[1], (int)position.y+1);
    
    if(velocity.y > 0 &&
       (data[0] == 1 || data[1] == 1 || data[2] == 1 || data[3] == 1)) {
           velocity.y = 0;
       }
    
    position.y += velocity.y;
}
void Camera::Jump() {
    velocity.y = 0.2;
}
bool Camera::IsComparePosition(float x, float y, float z) {
    if(fabs(position.x - x) <= 1 && fabs(position.y - y) <= 1 &&
       fabs(position.z - z) <= 1)
        return true;
    return false;
}
