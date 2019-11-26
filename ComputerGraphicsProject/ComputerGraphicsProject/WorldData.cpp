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
            
            //perlinNoise.noise(10 * x/SizeX, 10 * z/SizeZ, 0.8);
            int y = 20 * perlinNoise.noise((double)x/SizeX, (double)z/SizeZ, 0.8);
            
            //y -= 10;
            if(y < 0)
                y = 0;
            
            ck[z][x][y] = 1;
        }
    }
}
