//
//  main.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "GLManager.hpp"

//OpenGL 관리 클래스
GLManager glMNG;

int main(int argc, char * argv[]) {
    
    //맥 XCode로 실행시 파일 접근 경로가 달라 수동으로 접근 절대 경로를 설정
    chdir("/Users/liunx/Desktop/backup/computerGraphics/lab/ComputerGraphicsProject/ComputerGraphicsProject/");
    
    glMNG.Init(&argc, argv);
    
    glMNG.Loop();
    
    return 0;
}
