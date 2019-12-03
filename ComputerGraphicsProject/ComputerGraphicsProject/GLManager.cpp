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
vector<GLTex*> GLManager::textureList;

Camera cam;
World world;

static int rots = 0;
static int selectItem = 0;

GLfloat materialAmbient[] = {1, 1, 1, 1};
GLfloat materialDiffuse[] = {1, 1, 1, 1};
GLfloat materialSpecular[] = {1, 1, 1, 1};
GLfloat materialShininess[] = {100};

////////////////////////

void GLManager::LoadGLTextures() {
    LoadBMP("mineTex.bmp");
    textureList.push_back(new GLTex());
    textureList[textureList.size()-1]->bit = GetBMP("mineTex.bmp");
    textureList[textureList.size()-1]->bit->SetOffset(16, 16);
    glGenTextures(1, &textureList[textureList.size()-1]->objIndex);
    glBindTexture(GL_TEXTURE_2D, textureList[textureList.size()-1]->objIndex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textureList[textureList.size()-1]->bit->width, textureList[textureList.size()-1]->bit->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureList[textureList.size()-1]->bit->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}

////////////////////////

void GLManager::LightInit() {
    GLfloat lightAmbient[] = {1, 1, 1, 1.0};
    GLfloat lightDiffuse[] = {1, 1, 1, 1.0};
    GLfloat lightSpecular[] = {1, 1, 1, 1.0};
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    
    GLfloat lightPosition[] = {0, -1, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    GLfloat lightDir[3];
    lightDir[0] = 0;
    lightDir[1] = 0;
    lightDir[2] = -1;
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
    GLfloat spotAngle[] = {25.0};
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
}

void GLManager::Init(int * argc, char * argv[]) {
    glutInit(argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("OpenGl Exampel Drawing");
    glClearColor(0, 0, 0, 0);
    
    LoadGLTextures();
    
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
    glutPassiveMotionFunc(input.SetMouseMove);
    
    LightInit();
    
    glutSetCursor(GLUT_CURSOR_NONE);
    glutFullScreen();
    glutDisplayFunc(Rendering);
    
    world.Init();
}
void GLManager::DrawVoxel(int x, int y, int z, int type) {
    glPushMatrix();
    
    glTranslated(x, y, -z);
    
    for(int i=0; i<6; i++) {
        
        /*materialDiffuse[0] = voxelColor[i].r;
         materialDiffuse[1] = voxelColor[i].g;
         materialDiffuse[2] = voxelColor[i].b;
         
         materialAmbient[0] = voxelColor[i].r;
         materialAmbient[1] = voxelColor[i].g;
         materialAmbient[2] = voxelColor[i].b;
         
         materialSpecular[0] = voxelColor[i].r;
         materialSpecular[1] = voxelColor[i].g;
         materialSpecular[2] = voxelColor[i].b;*/
        
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
        glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
        
        glColor4f(voxelColor[i].r, voxelColor[i].g, voxelColor[i].b, voxelColor[i].a);
        glBegin(GL_QUADS);
        for(int j=0; j<4; j++) {
            
            glTexCoord2f(
                         textureList[textureList.size()-1]->bit->GetOffsetX(j, voxelTexture[type][i]),
                         textureList[textureList.size()-1]->bit->GetOffsetY(j, voxelTexture[type][i]));
            
            glVertex3f(voxelPos[voxelIndex[i][j]].x, voxelPos[voxelIndex[i][j]].y, voxelPos[voxelIndex[i][j]].z);
        }
        glEnd();
    }
    
    glPopMatrix();
}
void GLManager::DrawUI() {
    glDisable(GL_LIGHTING);
    
    float uiZPosition = -0.2f;
    
    glBegin(GL_LINES);
    glColor4f(1, 0, 0, 1);
    glVertex3f(0.01, 0.01, uiZPosition);
    glVertex3f(-0.01, -0.01, uiZPosition);
    glVertex3f(-0.01, 0.01, uiZPosition);
    glVertex3f(0.01, -0.01, uiZPosition);
    glEnd();
    
    int tex[5] = {245, 1, 2, 4, 7};
    for(int i=0; i<5; i++) {
        glColor3f(0.6, 0.6, 0.6);
        if(selectItem == i)
            glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glTexCoord2f(
                     textureList[textureList.size()-1]->bit->GetOffsetX(0, tex[i]),
                     textureList[textureList.size()-1]->bit->GetOffsetY(0, tex[i]));
        glVertex3f((i-1) * 0.025, -0.09, uiZPosition);
        glTexCoord2f(
                     textureList[textureList.size()-1]->bit->GetOffsetX(1, tex[i]),
                     textureList[textureList.size()-1]->bit->GetOffsetY(1, tex[i]));
        glVertex3f((i-2) * 0.025, -0.09, uiZPosition);
        glTexCoord2f(
                     textureList[textureList.size()-1]->bit->GetOffsetX(2, tex[i]),
                     textureList[textureList.size()-1]->bit->GetOffsetY(2, tex[i]));
        glVertex3f((i-2) * 0.025, -0.11, uiZPosition);
        glTexCoord2f(
                     textureList[textureList.size()-1]->bit->GetOffsetX(3, tex[i]),
                     textureList[textureList.size()-1]->bit->GetOffsetY(3, tex[i]));
        glVertex3f((i-1) * 0.025, -0.11, uiZPosition);
        glEnd();
    }
    
    glEnable(GL_LIGHTING);
}
void GLManager::Rendering() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //glColor3f(1, 0, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    DrawUI();
    
    gluLookAt(cam.position.x, cam.position.y, cam.position.z,
              cam.position.x + cam.look.x, cam.position.y - cam.look.y, cam.position.z - cam.look.z,
              0.0, 1.0, 0.0);
    
    glPushMatrix();
    
    for(int z=0; z < SizeZ; z++) {
        for(int x = 0; x < SizeX; x++) {
            for(int y = 0; y < SizeY; y++) {
                if((abs(cam.position.x - x) >= 20) || (abs(-cam.position.z - z) >= 20))
                    continue;
                
                if(world.ck[z][x][y].type != 0 && world.ck[z][x][y].visual) {
                    DrawVoxel(x, y, z, world.ck[z][x][y].type - 1);
                }
            }
        }
    }
    
    glPopMatrix();
    
    //glFlush();
    
    glutSwapBuffers();
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
    if(input.GetKey(KeyType::q) == InputState::stay)
        rots = (rots + 1) % 360;
    if(input.GetKey(KeyType::e) == InputState::stay)
        rots = (rots - 1) % 360;
    if(input.GetKey(KeyType::space) == InputState::down)
        cam.Jump();
    if(input.GetKey(KeyType::leftArrow) == InputState::stay)
        cam.Rotate({0, -0.03, 0});
    if(input.GetKey(KeyType::rightArrow) == InputState::stay)
        cam.Rotate({0, 0.03, 0});
    if(input.GetKey(KeyType::_1) == InputState::down)
        selectItem = 0;
    if(input.GetKey(KeyType::_2) == InputState::down)
        selectItem = 1;
    if(input.GetKey(KeyType::_3) == InputState::down)
        selectItem = 2;
    if(input.GetKey(KeyType::_4) == InputState::down)
        selectItem = 3;
    if(input.GetKey(KeyType::_5) == InputState::down)
        selectItem = 4;
    if(input.GetKey(KeyType::upArrow) == InputState::stay)
        cam.Rotate({-0.03, 0, 0});
    if(input.GetKey(KeyType::downArrow) == InputState::stay)
        cam.Rotate({0.03, 0, 0});
    if(input.GetMouseDown(MouseType::left)) {
        if(selectItem == 0)
            RemoveBlock();
        else
            AddBlock();
    }
    if(input.GetKey(KeyType::t) == InputState::down) {
        AddBlock();
    }
    //if(input.GetMouseStay(MouseType::left)) {
        cam.Rotate({
            input.GetMouseChangeRate().y / 100.0f,
            input.GetMouseChangeRate().x / 100.0f, 0});
    //}
    
    
    for(int i=0; i<funcList.size(); i++) {
        funcList[i]();
    }
    
    input.InputUpdate();
    
    glutPostRedisplay();
}
void GLManager::RemoveBlock() {
    for(float i=1.0f; i<5.0f; i+=0.2f) {
        float _x = cam.position.x + cam.look.x * i;
        float _y = cam.position.y - cam.look.y * i;
        float _z = cam.position.z - cam.look.z * i;
        
        _z = -_z;
        
        int data = world.GetDataAround(&_z, &_x, &_y);
        if(data != 0 && world.ck[(int)_z][(int)_x][(int)_y].visual) {
            world.Remove((int)_z, (int)_x, (int)_y);
            break;
        }
    }
}
void GLManager::AddBlock() {
    for(float i=1.0f; i<5.0f; i+=0.2f) {
        
        float _x = cam.position.x + cam.look.x * i;
        float _y = cam.position.y - cam.look.y * i;
        float _z = cam.position.z - cam.look.z * i;
        _z = -_z;
        
        int data = world.GetDataAround(&_z, &_x, &_y);
        if(data != 0 && world.ck[(int)_z][(int)_x][(int)_y].visual) {
            float _x = cam.position.x + cam.look.x * (i-1);
            float _y = cam.position.y - cam.look.y * (i-1);
            float _z = cam.position.z - cam.look.z * (i-1);
            if(cam.IsComparePosition(_x, _y, _z))
                break;
            _z = -_z;
            world.Add((int)_z, (int)_x, (int)_y, selectItem+1);
            break;
        }
    }
}

void GLManager::AddCBFunc(FuncPtr ptr) {
    funcList.push_back(ptr);
}


