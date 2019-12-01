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

Camera cam;
World world;

void LightInit() {
    GLfloat globalAmbient[] = {0.1, 0.1, 0.1, 1.0};
    
    GLfloat light0Ambient[] = {1, 1, 1, 1.0};
    GLfloat light0Diffuse[] = {0.5, 0.4, 0.3, 1.0};
    GLfloat light0Specular[] = {1.0, 1.0, 1.0, 1.0};
    
    GLfloat materialAmbient[] = {1, 1, 1, 1.0};
    GLfloat materialDiffuse[] = {1, 1, 1, 1.0};
    GLfloat materialSpecular[] = {0.0, 0.0, 1.0, 1,0};
    GLfloat materialShininess[] = {25};
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light0Specular);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void GLManager::Init(int * argc, char * argv[]) {
    glutInit(argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(0, 0, 0, 0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 0.1, 50.0);
    
    glutIdleFunc(CBIdle);
    
    glutKeyboardFunc(input.SetKeyDown);
    glutSpecialFunc(input.SetSpecialKeyDown);
    glutKeyboardUpFunc(input.SetKeyUp);
    glutSpecialUpFunc(input.SetSpecialKeyUp);
    
    glutMouseFunc(input.SetMousePress);
    glutMotionFunc(input.SetMouseMove);
    
    LightInit();
    
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
            glVertex3f(voxelPos[voxelIndex[i][j]].x+0.5, voxelPos[voxelIndex[i][j]].y, voxelPos[voxelIndex[i][j]].z);
        }
        glEnd();
    }
    
    glPopMatrix();
}
void GLManager::Rendering() {
    //glViewport(0, 0, 600, 600);
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    
    GLfloat lightPosition0[] = {0.0, 1.0, -10.0, 1.0};
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition0);
    
    gluLookAt(cam.position.x, cam.position.y, cam.position.z,
              cam.position.x + cam.look.x, cam.position.y - cam.look.y, cam.position.z - cam.look.z,
              0.0, 1.0, 0.0);
    
    glPushMatrix();
    
    for(int z=0; z < SizeZ; z++) {
        for(int x = 0; x < SizeX; x++) {
            for(int y = 0; y < SizeY; y++) {
                if((abs(cam.position.x - x) >= 20) || (abs(-cam.position.z - z) >= 20))
                    continue;
                
                if(world.ck[z][x][y].type == 1 && world.ck[z][x][y].visual) {
                    DrawVoxel(x, y, z);
                }
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
    cam.Gravity();
    
    if(input.GetKey(KeyType::w) == InputState::stay)
        cam.Translate({0, 0, -1}, true);
    if(input.GetKey(KeyType::s) == InputState::stay)
        cam.Translate({0, 0, 1}, true);
    if(input.GetKey(KeyType::a) == InputState::stay)
        cam.Translate({-1, 0, 0}, false);
    if(input.GetKey(KeyType::d) == InputState::stay)
        cam.Translate({1, 0, 0}, false);
    if(input.GetKey(KeyType::space) == InputState::down)
        cam.Jump();
    if(input.GetKey(KeyType::leftArrow) == InputState::stay)
        cam.Rotate({0, -0.03, 0});
    if(input.GetKey(KeyType::rightArrow) == InputState::stay)
        cam.Rotate({0, 0.03, 0});
    if(input.GetKey(KeyType::upArrow) == InputState::stay)
        cam.Rotate({-0.03, 0, 0});
    if(input.GetKey(KeyType::downArrow) == InputState::stay)
        cam.Rotate({0.03, 0, 0});
    if(input.GetMouseStay(MouseType::left)) {
        cam.Rotate({
            input.GetMouseChangeRate().y / 100.0f,
            input.GetMouseChangeRate().x / 100.0f, 0});
    }
    if(input.GetMouseDown(MouseType::left)) {
        for(int i=1; i<5; i++) {
            int _x = (int)round(cam.position.x - 0.5 + cam.look.x * i);
            int _y = (int)round(cam.position.y - 0.5 - cam.look.y * i);
            int _z = (int)round(cam.position.z - cam.look.z * i);
            if(world.IsValidPos(_x, _y, -_z)) {
                int data = world.ck[-_z][_x][_y].type;
                if(data == 1 && world.ck[-_z][_x][_y].visual) {
                    //world.ck[-_z][_x][_y].type = 0;
                    //world.ck[-_z][_x][_y].visual = false;
                    world.Remove(_x, _y, -_z);
                    break;
                }
            }
        }
    }
    if(input.GetKey(KeyType::t) == InputState::down) {
        for(int i=1; i<5; i++) {
            int _x = (int)round(cam.position.x - 0.5 + cam.look.x * i);
            int _y = (int)round(cam.position.y - 0.5 - cam.look.y * i);
            int _z = (int)round(cam.position.z - cam.look.z * i);
            if(world.IsValidPos(_x, _y, -_z)) {
                int data = world.ck[-_z][_x][_y].type;
                if(data == 1 && world.ck[-_z][_x][_y].visual) {
                    _x = (int)round(cam.position.x - 0.5 + cam.look.x * (i-1));
                    _y = (int)round(cam.position.y - 0.5 - cam.look.y * (i-1));
                    _z = (int)round(cam.position.z - cam.look.z * (i-1));
                    world.Add(_x, _y, -_z, 1);
                    break;
                }
            }
        }
    }
    
    
    for(int i=0; i<funcList.size(); i++) {
        funcList[i]();
    }
    
    input.InputUpdate();
    
    glutPostRedisplay();
}

void GLManager::AddCBFunc(FuncPtr ptr) {
    funcList.push_back(ptr);
}


