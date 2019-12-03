//
//  BitmapMNG.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 12. 2..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef BitmapMNG_hpp
#define BitmapMNG_hpp

#include <stdio.h>
#include <vector>
#include <string.h>

typedef struct BITMAP {
    int width, height;
    int sizeX, sizeY;
    float offsetX, offsetY;
    char fileName[20];
    unsigned char * data;
    void SetOffset(int x, int y) {
        sizeX = x;
        sizeY = y;
        offsetX = 1.0f / (float)x;
        offsetY = 1.0f / (float)y;
    }
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

extern std::vector<Bitmap*> bitmapList;

void LoadBMP(const char fileName[]);
Bitmap* GetBMP(const char fileName[]);

#endif /* BitmapMNG_hpp */
