//
//  WorldData.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef WorldData_hpp
#define WorldData_hpp

#define SizeX 100
#define SizeY 50
#define SizeZ 100

typedef int Chunk[SizeZ][SizeX][SizeY];

class World {
public:
    Chunk ck;
public:
    World();
    void Init();
};

extern World world;

#endif /* WorldData_hpp */
