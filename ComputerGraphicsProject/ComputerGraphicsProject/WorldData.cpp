//
//  WorldData.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "WorldData.hpp"
#include "PerlinNoise.hpp"

#include <stdio.h>
#include <cmath>

void World::Init() {

    //맵 초기화
    for(int z=0; z<SizeZ; z++) {
        for(int x=0; x<SizeX; x++) {
            for(int y = 0; y < SizeY; y++) {
                ck[z][x][y].type = 0;
                ck[z][x][y].visual = false;
            }
        }
    }
    
    //맵 랜덤 정보 입력
    for(int z=0; z<SizeZ; z++) {
        for(int x=0; x<SizeX; x++) {
            
            //노이즈 y좌표 높이 설정
            int y = 20 * perlinNoise.noise(
                    (double)x/SizeX, (double)z/SizeZ, 0.8);
            
            if(y < 0)
                y = 0;
            
            //y좌표 기본 블럭 입력
            ck[z][x][y].type = 6;
            ck[z][x][y].visual = true;
            int downY = y - 1;
            
            //y좌표 밑 기타 정보 입력
            while(downY > 0) {
                if(y - downY < 4)
                    ck[z][x][downY].type = 7;
                else
                    ck[z][x][downY].type = 8;
                ck[z][x][downY].visual = false;
                downY -= 1;
            }
        }
    }
}

bool World::IsValidPos(int z, int x, int y) {
    if(x < 0 || x >= SizeX)
        return false;
    if(y < 0 || y >= SizeY)
        return false;
    if(z < 0 || z >= SizeZ)
        return false;
    return true;
}

void World::Remove(int z, int x, int y) {
    ck[z][x][y].type = 0;
    ck[z][x][y].visual = false;
    
    VisualAround(z, x, y);
}

void World::VisualAround(int z, int x, int y) {
    if(IsValidPos(z, x+1, y) && ck[z][x+1][y].type != 0)
        ck[z][x+1][y].visual = true;
    if(IsValidPos(z, x-1, y) && ck[z][x-1][y].type != 0)
        ck[z][x-1][y].visual = true;
    if(IsValidPos(z, x, y+1) && ck[z][x][y+1].type != 0)
        ck[z][x][y+1].visual = true;
    if(IsValidPos(z, x, y-1) && ck[z][x][y-1].type != 0)
        ck[z][x][y-1].visual = true;
    if(IsValidPos(z+1, x, y) && ck[z+1][x][y].type != 0)
        ck[z+1][x][y].visual = true;
    if(IsValidPos(z-1, x, y) && ck[z-1][x][y].type != 0)
        ck[z-1][x][y].visual = true;
}

void World::Add(int z, int x, int y, int type) {
    ck[z][x][y].type = type;
    ck[z][x][y].visual = true;
}

int World::GetData(int z, int x, int y) {
    if(IsValidPos(z, x, y))
        if(ck[z][x][y].visual)
            return ck[z][x][y].type;
    return -1;
}
bool World::IsInnerPos(int z, int x, int y,
                       float posZ, float posX, float posY) {
    bool isInner = true;
    
    if((posX > x+1) || (posX < x))
        isInner = false;
    if((posZ > z+1) || (posZ < z))
        isInner = false;
    if((posY > y+0.5) || (posY < y - 0.5))
        isInner = false;
    
    return isInner;
}
int World::GetDataAround(float * z, float * x, float * y) {
    int data = -1;
    
    int offsetX = *x, offsetY = *y, offsetZ = *z;
    
    //좌표 주변 검사
    for(int cZ = -1; cZ <= 1; cZ++) {
        for(int cX = -1; cX <= 1; cX++) {
            for(int cY = -1; cY <= 1; cY++) {
                int dx = offsetX + cX;
                int dy = offsetY + cY;
                int dz = offsetZ + cZ;
                
                if(IsValidPos(dz, dx, dy)) {
                    if(IsInnerPos(dz, dx, dy, *z, *x, *y) &&
                       ck[dz][dx][dy].visual) {
                        *z = dz;
                        *x = dx;
                        *y = dy;
                        
                        return ck[dz][dx][dy].type;
                    }
                }
            }
        }
    }
    
    return data;
}

