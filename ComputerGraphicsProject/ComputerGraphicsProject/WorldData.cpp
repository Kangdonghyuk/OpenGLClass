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

World::World() {
   
}

void World::Init() {
    bzero(ck, SizeZ * SizeX * SizeY);
    for(int z=0; z<SizeZ; z++) {
        for(int x=0; x<SizeX; x++) {
            
            int y = 20 * perlinNoise.noise(
                    (double)x/SizeX, (double)z/SizeZ, 0.8);
            
            if(y < 0)
                y = 0;
            
            ck[z][x][y].type = 1;
            ck[z][x][y].visual = true;
            y -= 1;
            
            while(y > 0) {
                ck[z][x][y].type = 1;
                ck[z][x][y].visual = false;
                y -= 1;
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
    
    for(int cZ = -1; cZ <= 1; cZ++) {
        for(int cX = -1; cX <= 1; cX++) {
            for(int cY = -1; cY <= 1; cY++) {
                int dx = offsetX + cX;
                int dy = offsetY + cY;
                int dz = offsetZ + cZ;
                
                if(IsValidPos(dz, dx, dy)) {
                    if(IsInnerPos(dz, dx, dy, *z, *x, *y)) {
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

