//
//  main.cpp
//  openGLTest
//
//  Created by Liunx on 2019. 9. 9..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

float count = 5;

void OnDisplay(void) {
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    /*glBegin(GL_TRIANGLES);
     
     glVertex2d(0.0, 0.1);
     glVertex2d(-0.1, -0.1);
     glVertex2d(0.1, -0.1);
     
     glEnd();
     
     glBegin(GL_TRIANGLES);
     
     glVertex2d(0.5, 0.7);
     glVertex2d(0.3, 0.3);
     glVertex2d(0.7, 0.3);
     
     glEnd();*/
    
    glLineWidth(5.5f);
    glPointSize(5.5f);
    glBegin(GL_POINTS);
    
    for(float i=-1; i<1; ) {
        glVertex2f(sin(i), sin((i+count)*13)/5);
        i += 0.01f;
    }
    
    glEnd();
    
    count += 0.03f;
    
    if(count >= 10.0f)
        count = 0.0f;
    
    glutPostRedisplay();
    
    glFlush();
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutCreateWindow("testOpenGLWindow");
    glutDisplayFunc(OnDisplay);
    glutMainLoop();
    
    return 0;
}
///Users/liunx/Downloads/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/
