//
//  WorldData.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 26..
//  Copyright © 2019년 Liunx. All rights reserved.
//

//월드 관리 클래스

#ifndef WorldData_hpp
#define WorldData_hpp

//월드 사이즈 (3차원 배열)
#define SizeX 100
#define SizeY 50
#define SizeZ 100

//월드 각 블럭 상태 구조체
typedef struct CHUNKDATA {
    int type;
    bool visual;
}ChunkData;

//3차원 배열 청크 자료형 정의
typedef ChunkData Chunk[SizeZ][SizeX][SizeY];

class World {
public:
    //맵 정보 배열
    Chunk ck;
public:
    void Init(); //월드 초기화
    void Remove(int z, int x, int y); //해당 블럭 제거
    void VisualAround(int z, int x, int y); //제거시 주변 블럭 보이기
    bool IsValidPos(int z, int x, int y); //좌표 유효성 확인
    void Add(int z, int x, int y, int type); //블럭 추가
    int GetData(int z, int x, int y); //좌표 해당 블럭 타입 반환
    int GetDataAround(float * z, float * x, float * y); //좌표 인근 블럭 타입 반환
    bool IsInnerPos(int z, int x, int y, //GetDataAround에서 호출하며 좌표 범위 체크
                    float posZ, float posX, float posY);
};

extern World world;

#endif /* WorldData_hpp */
