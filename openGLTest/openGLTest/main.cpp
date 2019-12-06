#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


#define Width 4
#define Height 4

GLubyte MyTexture[Width][Height][3];

void FillMyTexture() {
    int s, t;
    for(s = 0; s < Width; s++) {
        for(t = 0; t < Height; t++) {
            GLubyte Intensity = ((s + t) % 2) * 255;
            MyTexture[s][t][0] = Intensity;
            MyTexture[s][t][1] = Intensity;
            MyTexture[s][t][2] = Intensity;
        }
    }
}

void MyInit() {
    glClearColor(0, 0, 0, 0);
    FillMyTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, &MyTexture[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 0);
    glTexCoord2f(0, 3);
    glVertex3f(-1, 1, 0);
    glTexCoord2f(3, 3);
    glVertex3f(1, 1, 0);
    glTexCoord2f(3, 0);
    glVertex3f(1, -1, 0);
    glEnd();
    glutSwapBuffers();
}

int main (int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OP");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    
    return 0;
}

