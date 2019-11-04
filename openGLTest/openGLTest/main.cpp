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

void InitLight() {
    GLfloat mat_diffuse[] = {0.5, 0.4, 0.3, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[] = {0.5, 0.4, 0.3, 1.0};
    GLfloat mat_shininess[] = {15};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_position[] = {-3, 6, 3.0, 0.0};
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1, 0, 0, -1, 0, 1, 0);
    glutSolidTeapot(0.5);
    glFlush();
}

void MyDisplay2(void) {
    glClearColor(1, 1, 1, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-5, 5, -5, 5, -5, 5);
    //glFrustum(-5, 5, -5, 5, 0.5, 10);
    gluPerspective(100, 400/400, 1, 10);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 1, 2, 0, 0, 0, 0, 1, 0);
    //gluLookAt(0, 5, 3, 0, 0, 0, 0, 1, 0);
    //gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
    //gluLookAt(2, 1, 1, 0, 0, 0, 0, 1, 0);
    
    glColor3f(0, 0, 1);
    
    glBegin(GL_QUADS);
    glVertex3f(-2, 0, 2);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 0, -2);
    glVertex3f(-2, 0, -2);
    glEnd();
    
    //glTranslatef(2, 0, 0);
    
    //glutWireTeapot(3);
    
    glFlush();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
    //InitLight();
    glutDisplayFunc(MyDisplay2);
    glutMainLoop();
    
    return 0;
}
