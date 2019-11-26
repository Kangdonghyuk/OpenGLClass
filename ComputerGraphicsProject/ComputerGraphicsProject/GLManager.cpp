//
//  GLManager.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "GLManager.hpp"

using namespace std;

vector<FuncPtr> GLManager::funcList;

//Camera cam;

void GLManager::Init(int * argc, char * argv[]) {
    glutInit(argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(0, 0, 0, 0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 50.0);
    
    glutIdleFunc(CBIdle);
    glutKeyboardFunc(CBKeyboard);
    glutDisplayFunc(Rendering);
    
    world.Init();
}
void DrawVoxel(int x, int y, int z) {
    glPushMatrix();
    
    glTranslated(x, y, -z);
    
    for(int i=5; i>=0; i--) {
        glColor4f(voxelColor[i].r, voxelColor[i].g, voxelColor[i].b, voxelColor[i].a);
        glBegin(GL_QUADS);
        for(int j=0; j<4; j++) {
            glVertex3f(voxelPos[voxelIndex[i][j]].x, voxelPos[voxelIndex[i][j]].y, voxelPos[voxelIndex[i][j]].z);
        }
        glEnd();
    }
    
    glPopMatrix();
}
void GLManager::Rendering() {
    glViewport(0, 0, 600, 600);
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(cam.position.x, cam.position.y, cam.position.z,
              cam.position.x + cam.look.x, cam.position.y - cam.look.y, cam.position.z - cam.look.z,
              0.0, 1.0, 0.0);
    
    glPushMatrix();
    
    for(int z=0; z < SizeZ; z++) {
        for(int x = 0; x < SizeX; x++) {
            for(int y = 0; y < SizeY; y++) {
                if((abs(cam.position.x - x) >= 20) && (abs(cam.position.z - z) >= 20))
                    continue;
                
                if(world.ck[z][x][y] == 1) {
                    DrawVoxel(x, y, z);
                }
            }
        }
    }
    DrawVoxel(0, 0, 0);
    
    //DrawVoxel(15, 5, 15);
    
    glPopMatrix();
    
    glFlush();
}
void GLManager::Loop() {
    glutMainLoop();
}
void GLManager::CBIdle() {
    for(int i=0; i<funcList.size(); i++) {
        funcList[i]();
    }
    
    glutPostRedisplay();
}
void GLManager::CBKeyboard(unsigned char key, int x, int y) {
    if(key == 'w') {
        cam.Translate({0, 0, -1}, true);
    }
    else if(key == 's') {
        cam.Translate({0, 0, 1}, true);
    }
    else if(key == 'a') {
        cam.Translate({-1, 0, 0}, false);
    }
    else if(key == 'd') {
        cam.Translate({1, 0, 0}, false);
    }
    /*else if(key == 'q') {
     cam.Translate({-1, 0, -1}, true);
     }
     else if(key == 'e') {
     cam.Translate({1, 0, -1}, true);
     }*/
    else if(key == 'q') {
        cam.Rotate({0, -0.1, 0});
    }
    else if(key == 'e') {
        cam.Rotate({0, 0.1, 0});
    }
    
}

void GLManager::AddCBFunc(FuncPtr ptr) {
    funcList.push_back(ptr);
}


