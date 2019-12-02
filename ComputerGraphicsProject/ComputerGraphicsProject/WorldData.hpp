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

typedef struct CHUNKDATA {
    int type;
    bool visual;
}ChunkData;

typedef ChunkData Chunk[SizeZ][SizeX][SizeY];

class World {
public:
    Chunk ck;
public:
    World();
    void Init();
    void Remove(int x, int y, int z);
    void VisualAround(int x, int y, int z);
    bool IsValidPos(int x, int y, int z);
    void Add(int x, int y, int z, int type);
    int GetData(int z, int x, int y);
};

extern World world;

#endif /* WorldData_hpp */
