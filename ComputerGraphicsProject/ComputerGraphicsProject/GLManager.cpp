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

float lz = 0;
float lx = 0;
float ly = 0;

Camera cam;

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
}
void DrawVoxel(int x, int y, int z) {
    glPushMatrix();
    
    glTranslated(x-15, y-5, -z + 15);
    
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
    
    
    float _z = cosf(ly);
    float _x = sinf(ly);
    
    printf("%f : %f \n", _x, _z);
    
    gluLookAt(lx, 0.0, lz, lx + _x, 0.0, lz - _z, 0.0, 1.0, 0.0);
    
    glPushMatrix();
    
    //glRotated(ly, 0, 1, 0);
    //glTranslated(-lx, 0, -lz);
    //glScaled(0.2, 0.2, 0.2);
    
    for(int z=0; z < 30; z++) {
        for(int x = 0; x < 30; x++) {
            DrawVoxel(x, 0, z);
            if(z == 0 || z == 29) {
                for(int y=0; y<10; y++)
                    DrawVoxel(x, y, z);
            }
            else if(x == 0 || x == 29) {
                for(int y=0; y<10; y++)
                    DrawVoxel(x, y, z);
            }
            
        }
    }
    
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
    float _z = cosf(ly);
    float _x = sinf(ly);
    
    if(key == 'w') {
        //forceZ = -1;
        lz -= _z;
        lx += _x;
    }
    else if(key == 's') {
        //forceZ = 1;
        lz += _z;
        lx -= _x;
    }
    else if(key == 'a') {
        //forceX = -1;
        lz -= _x;
        lx -= _z;
    }
    else if(key == 'd') {
        //forceX = 1;
        lz += _x;
        lx += _z;
    }
    else if(key == 'q') {
        ly -= 0.1;
    }
    else if(key == 'e') {
        ly += 0.1;
    }
    
    //lz += forceZ * _x;
    //lx += forceX * _z;
}

void GLManager::AddCBFunc(FuncPtr ptr) {
    funcList.push_back(ptr);
}


