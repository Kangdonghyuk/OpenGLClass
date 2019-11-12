#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <vector>
#include <math.h>

using namespace std;

float colorModel[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

typedef struct VERTEX {
    float x, y;
}vertex;

class LineStrip {
public:
    int lineColorModelIndex;
    vertex startPosition;
    vector<vertex> wayPositionList;
    
    LineStrip(int lineColorModelIndex, float posX, float posY) {
        this->lineColorModelIndex = lineColorModelIndex;
        startPosition.x = posX;
        startPosition.y = posY;
    }
    
    void AddWayPosition(float posX, float posY) {
        vertex wayPos;
        wayPos.x = posX;
        wayPos.y = posY;
        wayPositionList.push_back(wayPos);
    }
};

vector<LineStrip*> lineStripList;
bool isDrawing = false;
int colorModelIndex = 0;

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    for(int i=0; i<3; i++) {
        glBegin(GL_QUADS);
        glColor3fv(colorModel[i]);
        glVertex2f(500, 500 - (i * 50));
        glVertex2f(450, 500 - (i * 50));
        glVertex2f(450, 450 - (i * 50));
        glVertex2f(500, 450 - (i * 50));
        glEnd();
    }
    
    for(int i=0; i<lineStripList.size(); i++) {
        glBegin(GL_LINE_STRIP);
        glColor3fv(colorModel[lineStripList[i]->lineColorModelIndex]);
        glVertex2f(lineStripList[i]->startPosition.x, lineStripList[i]->startPosition.y);
        for(int j=0; j<lineStripList[i]->wayPositionList.size(); j++) {
            glVertex2f(lineStripList[i]->wayPositionList[j].x, lineStripList[i]->wayPositionList[j].y);
        }
        glEnd();
    }
    
    glFlush();
}

void MyMouseClick(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = (500 - y);
        if(x >= 450 && y >= 350) {
            y = y-350;
            colorModelIndex = (2 - (y / 50));
        }
        else {
            lineStripList.push_back(new LineStrip(colorModelIndex, x, y));
            isDrawing = true;
        }
    }
    if(state == GLUT_UP) {
        isDrawing = false;
    }
}

void MyMouseMove(int x, int y) {
    y = 500 - y;
    if(isDrawing) {
        if(x >= 450 && y >= 350) {
            isDrawing = false;
            return ;
        }
        
        lineStripList[lineStripList.size() - 1]->AddWayPosition(x, y);
        glutPostRedisplay();
    }
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Painter");
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, 0, 500);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
