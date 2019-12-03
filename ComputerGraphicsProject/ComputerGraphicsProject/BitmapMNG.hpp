//
//  BitmapMNG.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 12. 2..
//  Copyright © 2019년 Liunx. All rights reserved.
//

/*
비트맵 로드 및 관리 헤더 파일
*/

#ifndef BitmapMNG_hpp
#define BitmapMNG_hpp

#include <stdio.h>
#include <vector>
#include <string.h>

//비트맵의 정보를 담는 구조체
typedef struct BITMAP {
    int width, height;
    int sizeX, sizeY;
    float offsetX, offsetY;
    char fileName[20];
    unsigned char * data;
    //텍스쳐 uv 매칭을 위해 가로 세로 구분 설정
    void SetOffset(int x, int y) {
        sizeX = x;
        sizeY = y;
        offsetX = 1.0f / (float)x;
        offsetY = 1.0f / (float)y;
    }
    //사각형 기준 각 버텍스와 이미지 인덱스 uv 좌표 반환
    float GetOffsetX(int index, int image) {
        float value = 0.0f;
        if(index == 0)
            value = (image % sizeX) * offsetX;
        if(index == 1)
            value = (image % sizeX) * offsetX + offsetX;
        if(index == 2)
            value = (image % sizeX) * offsetX + offsetX;
        if(index == 3)
            value = (image % sizeX) * offsetX;
        
        return value;
    }
    float GetOffsetY(int index, int image) {
        float value = 0.0f;
        if(index == 0)
            value = (sizeY - (image / sizeY)) * offsetY - offsetY;
        if(index == 1)
            value = (sizeY - (image / sizeY)) * offsetY - offsetY;
        if(index == 2)
            value = (sizeY - (image / sizeY)) * offsetY;
        if(index == 3)
            value = (sizeY - (image / sizeY)) * offsetY;
        
        return value;
    }
}Bitmap;

//비트맵 정보 배열
extern std::vector<Bitmap*> bitmapList;

//비트맵 로드, 비트맵 정보 배열에 추가
void LoadBMP(const char fileName[]);
//해당 파일 이름 비트맵 정보 반환
Bitmap* GetBMP(const char fileName[]);

#endif /* BitmapMNG_hpp */
