//
//  main.cpp
//  openGLTest
//
//  Created by Liunx on 2019. 9. 9..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>

void Init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, 0.5, 5);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Draw() {
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 0, -2);
    glVertex3f(-2, 0, -2);
    glVertex3f(-2, 0, 2);
    glEnd();
    glColor3f(1, 0, 0);
    glutWireTeapot(1);
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glViewport(0, 0, 250, 250);
    glPushMatrix();
    Init();
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    Draw();
    glPopMatrix();
    
    
    glViewport(250, 0, 250, 250);
    glPushMatrix();
    Init();
    gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0);
    Draw();
    glPopMatrix();
    
    
    glViewport(0, 250, 250, 250);
    glPushMatrix();
    Init();
    gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, -1);
    Draw();
    glPopMatrix();

    
    glViewport(250, 250, 250, 250);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1, 3, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
    Draw();

    
    glFlush();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(1, 1, 1, 1);
    
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    
    return 0;
}
