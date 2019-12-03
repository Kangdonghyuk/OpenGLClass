#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "bmp.hpp"


unsigned int MyTextureObject[1];
unsigned char *data;
int width;
int height;

static int rot;

void LoadBMP() {
    FILE *f = fopen("earth.bmp", "rb");
    unsigned char info[54];
    if(f != NULL) {
        fread(info, sizeof(unsigned char), 54, f);
        
        width = *(int*)&info[18];
        height = *(int*)&info[22];
        
        printf("%d %d\n", width, height);
        
        int size = 3*width*height; // for RGB
        
        data = new unsigned char[size];
        
        fread(data, sizeof(unsigned char), size, f);
        
        fclose(f);
        
        for(int i=0; i<size; i+=3){
            unsigned char temp = data[i];
            data[i] = data[i+2];
            data[i+2] = temp;
        }
    }
    else {
        printf("File NULL\n");
    }
    
}

void LoadGLTextures() {
    LoadBMP();
    glGenTextures(1, &MyTextureObject[0]);
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}


void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);
    
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, 1);
    glEnd();
    
    
    
    GLUquadricObj* earth;
    earth = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    gluQuadricDrawStyle(earth, GLU_FILL);
    gluQuadricTexture(earth, GL_TRUE);
    
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTranslatef(2, 2, 0);
    glRotatef(rot, 0, 1, 0);
    gluSphere(earth, 2, 100, 100);
    
    glFlush();
}

void Idle() {
    rot = (rot + 1) % 360;
    
    glutPostRedisplay();
}

int main (int argc, char* argv[])
{
    char buff[1024];
    chdir("/Users/liunx/Desktop/backup/computerGraphics/lab/openGLTest/openGLTest/");
    getcwd( buff, 1024);                   // 작업 디렉토리 구하기
    printf( "작업 디렉토리: %sn \n", buff);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL");
    
    LoadGLTextures();
    glutIdleFunc(Idle);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    
    return 0;
}

