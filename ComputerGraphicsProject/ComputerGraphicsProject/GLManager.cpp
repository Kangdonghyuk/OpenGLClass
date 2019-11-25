//
//  GLManager.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 21..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "GLManager.hpp"

using namespace std;

vector<Vertex> GLManager::vertexList;
vector<FuncPtr> GLManager::funcList;

float lz = 5;
float lx = 0;
float ly = 0;

void GLManager::Init(int * argc, char * argv[]) {
    glutInit(argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(0, 0, 0, 0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 20.0);
    
    glutIdleFunc(CBIdle);
    glutKeyboardFunc(CBKeyboard);
    glutDisplayFunc(Rendering);
    
}
void GLManager::Rendering() {
    glViewport(0, 0, 600, 600);
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    float _x = cosf(ly);
    float _z = sinf(ly);

    gluLookAt(lx, 0.0, lz, lx + _z, 0.0, lz - _x, 0.0, 1.0, 0.0);
    
    glPushMatrix();
    
    //glRotated(ly, 0, 1, 0);
    //glTranslated(-lx, 0, -lz);
    //glScaled(0.2, 0.2, 0.2);
    
    for(int z=0; z < 10; z++) {
        for(int y=0; y<10; y++) {
            for(int x = 0; x < 10; x++) {
                
                glPushMatrix();
                
                glTranslated((x-5) * 1.2, z-10, -z);
                
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
    if(key == 'w') {
        lz -= 0.3;
    }
    else if(key == 's') {
        lz += 0.3;
    }
    else if(key == 'a') {
        lx -= 0.3;
    }
    else if(key == 'd') {
        lx += 0.3;
    }
    else if(key == 'q') {
        ly -= 0.1;
    }
    else if(key == 'e') {
        ly += 0.1;
    }
}

void GLManager::AddVertex(Vertex newVertex) {
    vertexList.push_back(newVertex);
    
    if(vertexList.size() >= 10) {
        vertexList.erase(vertexList.begin());
    }
}

void GLManager::AddCBFunc(FuncPtr ptr) {
    funcList.push_back(ptr);
}


