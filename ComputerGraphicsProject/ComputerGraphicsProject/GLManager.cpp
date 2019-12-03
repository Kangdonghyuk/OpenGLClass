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

GLfloat materialAmbient[] = {1, 1, 1, 1};
GLfloat materialDiffuse[] = {1, 1, 1, 1};
GLfloat materialSpecular[] = {1, 1, 1, 1};
GLfloat materialShininess[] = {100};

////////////////////////

unsigned int MyTextureObject[1];
unsigned char *data;
int width;
int height;

void GLManager::LoadGLTextures() {
    LoadBMP("mineTex.bmp");
    textureList.push_back(new GLTex());
    textureList[textureList.size()-1]->bit = GetBMP("mineTex.bmp");
    //Bitmap * bit = GetBMP("mineTex.bmp");
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
    
    glutDisplayFunc(Rendering);
    
    world.Init();
}
void GLManager::DrawVoxel(int x, int y, int z, int type) {
    glPushMatrix();
    
    glTranslated(x, y, -z);
    
    glBindTexture(GL_TEXTURE_2D, textureList[textureList.size()-1]->objIndex);
    
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
void GLManager::Rendering() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

    
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
    if(input.GetKey(KeyType::upArrow) == InputState::stay)
        cam.Rotate({-0.03, 0, 0});
    if(input.GetKey(KeyType::downArrow) == InputState::stay)
        cam.Rotate({0.03, 0, 0});
    if(input.GetMouseDown(MouseType::left)) {
        //printf("%f \n", textureList[textureList.size()-1]->bit->GetOffsetX(1, 0));
        for(float i=1.0f; i<5.0f; i+=0.2f) {
            /*int _x = (int)round(cam.position.x - 0.5 + cam.look.x * i);
            int _y = (int)round(cam.position.y - 0.5 - cam.look.y * i);
            int _z = (int)round(cam.position.z - cam.look.z * i);
            _z = -_z;*/
            float _x = cam.position.x + cam.look.x * i;
            float _y = cam.position.y - cam.look.y * i;
            float _z = cam.position.z - cam.look.z * i;
      
            _z = -_z;
            /*int data = world.GetData(-_z, _x, _y);
            if(data == 1 && world.ck[-_z][_x][_y].visual) {
                world.Remove(-_z, _x, _y);
                break;
            }*/
            
            int data = world.GetDataAround(&_z, &_x, &_y);
            if(data != 0 && world.ck[(int)_z][(int)_x][(int)_y].visual) {
                world.Remove((int)_z, (int)_x, (int)_y);
                break;
            }
        }
    }
    if(input.GetKey(KeyType::t) == InputState::down) {
        /*for(int i=1; i<5; i++) {
            int _x = (int)round(cam.position.x - 0.5 + cam.look.x * i);
            int _y = (int)round(cam.position.y - 0.5 - cam.look.y * i);
            int _z = (int)round(cam.position.z - cam.look.z * i);
            int data = world.GetData(-_z, _x, _y);
            if(data == 1 && world.ck[-_z][_x][_y].visual) {
                _x = (int)round(cam.position.x - 0.5 + cam.look.x * (i-1));
                _y = (int)round(cam.position.y - 0.5 - cam.look.y * (i-1));
                _z = (int)round(cam.position.z - cam.look.z * (i-1));
                world.Add(-_z, _x, _y, 1);
                break;
            }
        }*/
        
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
                world.Add((int)_z, (int)_x, (int)_y, 1);
                break;
            }
        }
    }
    if(input.GetMouseStay(MouseType::left)) {
        cam.Rotate({
            input.GetMouseChangeRate().y / 100.0f,
            input.GetMouseChangeRate().x / 100.0f, 0});
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


