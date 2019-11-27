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

bool World::IsValidPos(int x, int y, int z) {
    if(x < 0 || x >= SizeX)
        return false;
    if(y < 0 || y >= SizeY)
        return false;
    if(z < 0 || z >= SizeZ)
        return false;
    return true;
}

void World::Remove(int x, int y, int z) {
    ck[z][x][y].type = 0;
    ck[z][x][y].visual = false;
    
    VisualAround(x, y, z);
}

void World::VisualAround(int x, int y, int z) {
    if(IsValidPos(x+1, y, z) && ck[z][x+1][y].type != 0)
        ck[z][x+1][y].visual = true;
    if(IsValidPos(x-1, y, z) && ck[z][x-1][y].type != 0)
        ck[z][x-1][y].visual = true;
    if(IsValidPos(x, y+1, z) && ck[z][x][y+1].type != 0)
        ck[z][x][y+1].visual = true;
    if(IsValidPos(x, y-1, z) && ck[z][x][y-1].type != 0)
        ck[z][x][y-1].visual = true;
    if(IsValidPos(x, y, z+1) && ck[z+1][x][y].type != 0)
        ck[z+1][x][y].visual = true;
    if(IsValidPos(x, y, z-1) && ck[z-1][x][y].type != 0)
        ck[z-1][x][y].visual = true;
}

void World::Add(int x, int y, int z, int type) {
    ck[z][x][y].type = type;
    ck[z][x][y].visual = true;
}


