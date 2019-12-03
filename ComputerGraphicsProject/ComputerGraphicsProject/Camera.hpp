//
//  Camera.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

/*
 카메라(플레이어) 정의 클래스
 */

#ifndef Camera_hpp
#define Camera_hpp

#include "VoxelData.h"

//각도 변환
#define PI 3.141592
#define DEGREE_TO_RADIAN(value) value * (PI / 180)
#define RADIAN_TO_DEGREE(value) value * (180 / PI)

class Camera {
public:
    Position position; // 위치
    Position direction; // 회전시 보조
    Position look;  // 시점 방향
    Position moveLook; //시점 방향 x,z 만 정규화
public:
    Position velocity; // 이동 가속도
public:
    Camera();
public:
    void Translate(Position pos, bool _isVertical); // 이동
    void Rotate(Position rot); // 회전
public:
    void Gravity(); // 중력 적용
    void Jump(); // 점프
public:
    //좌표 카메라 좌표랑 일치하는지 화인
    bool IsComparePosition(float x, float y, float z);
};

extern Camera cam;

#endif /* Camera_hpp */
