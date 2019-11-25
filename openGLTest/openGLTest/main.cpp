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

void MyLightInit() {
    GLfloat light0_ambient[] = {0.5, 0.4, 0.3, 1.0};
    GLfloat light0_diffuse[] = {0.5, 0.4, 0.3, 1.0};
    GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    GLfloat material_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat material_diffuse[] = {0.3, 0.3, 0.3, 1};
    GLfloat material_specular[] = {0, 1, 0, 1};
    GLfloat material_shininess[] = {40.0};
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    
    /*GLint n;
    glGetIntegerv(GL_MAX_LIGHTS, &n);
    printf("n = %d\n", n);*/
}

void MyDisplay(void) {
    GLfloat lightPosition[] = {0, 0, 2, 1};
    //GLfloat lightPosition[] = {0, 2, 2, 1};
    //GLfloat lightPosition[] = {2, 2, 2, 1};
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    gluLookAt(0.5, 0.5, 0.5, 0, 0, -1, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    glColor3f(1, 0, 0);
   // glTranslatef(0.3, 0.3, -0.5);
    glutSolidTorus(0.3, 0.6, 800, 800);
    
    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(0, 0, 0, 0);
    
    MyLightInit();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    
    glutMainLoop();
    
    return 0;
}
