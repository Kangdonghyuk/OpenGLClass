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
    void Remove(int z, int x, int y);
    void VisualAround(int z, int x, int y);
    bool IsValidPos(int z, int x, int y);
    void Add(int z, int x, int y, int type);
    int GetData(int z, int x, int y);
    int GetDataAround(float * z, float * x, float * y);
    bool IsInnerPos(int z, int x, int y,
                    float posZ, float posX, float posY);
};

extern World world;

#endif /* WorldData_hpp */
