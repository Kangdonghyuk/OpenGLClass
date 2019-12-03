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

//기본 위치 시점 설정
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
    
    //앞뒤 이동 좌우 이동 따로 처리
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
    
    int data;
    
    // 블럭 통과 불가하게 맵 정보 확인
    
    data = world.GetData(-(int)_z, (int)_x, (int)position.y);
    
    if(data > 0) {
        velocity.x = 0;
        velocity.z = 0;
    }
    
    for(int i = 0; i < 360; i+=45) {
        data = world.GetData(
                             (0.3f * cosf(DEGREE_TO_RADIAN(i)) + (-_z)),
                             (0.3f * sinf(DEGREE_TO_RADIAN(i)) + _x),
                             (int)position.y);
        
        if(data > 0) {
            velocity.x = 0;
            velocity.z = 0;
            break;
        }
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
    
    //회전 후 삼각함수 이용해 시점 적용
    
    moveLook.y = tanf(direction.y);
    moveLook.x = sinf(direction.x);
    moveLook.z = cosf(direction.z);
    
    look = moveLook.AllNormalize();
}
void Camera::Gravity() {
    //float _x = position.x + velocity.x;
    //float _z = position.z + velocity.z;
    
    float _x = position.x;
    float _z = position.z;
    
    int data;
    
    // 중력 적용 바닥 통과 불가하게 맵 정보 확인
    
    data = world.GetData(-(int)_z, (int)_x, (int)position.y-1);
    
    velocity.y -= 0.0098;
    if(velocity.y < 0 && data > 0) {
        velocity.y = 0;
    }
    
    for(int i = 0; i < 360; i+=45) {
        data = world.GetData(
                             (0.2f * cosf(DEGREE_TO_RADIAN(i)) + (-_z)),
                             (0.2f * sinf(DEGREE_TO_RADIAN(i)) + _x),
                             (int)position.y-1);
        
        if(velocity.y < 0 && data > 0) {
            velocity.y = 0;
            break;
        }
    }
    
    // 점프시 블럭 통과 불가하게 맵 정보 확인
    
    data = world.GetData(-(int)_z, (int)_x, (int)position.y+1);
    
    if(velocity.y > 0 && data > 0) {
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
