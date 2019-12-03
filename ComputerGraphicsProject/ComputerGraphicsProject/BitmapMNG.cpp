//
//  BitmapMNG.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 12. 2..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "BitmapMNG.hpp"

std::vector<Bitmap*> bitmapList;

void LoadBMP(const char * fileName) {
    FILE * f = fopen(fileName, "rb");
    unsigned char info[54];
    
    if(f != nullptr) {
        fread(info, sizeof(unsigned char), 54, f);
        
        bitmapList.push_back(new Bitmap());
        
        int index = (int)(bitmapList.size() - 1);
        
        bitmapList[index]->width = *(int*)&info[18];
        bitmapList[index]->height = *(int*)&info[22];
        
        int size = 3 * bitmapList[index]->width * bitmapList[index]->height;
        
        bitmapList[index]->data = new unsigned char[size];
        
        fread(bitmapList[index]->data,
              sizeof(unsigned char), size, f);
        
        strcpy(bitmapList[index]->fileName, fileName);
        
        fclose(f);
        
        for(int i=0; i<size; i+=3){
            unsigned char temp = bitmapList[index]->data[i];
            bitmapList[index]->data[i] = bitmapList[index]->data[i+2];
            bitmapList[index]->data[i+2] = temp;
        }
    }
    else {
        printf("File Null");
    }
}

Bitmap* GetBMP(const char * fileName) {
    for(int i=0; i<bitmapList.size(); i++) {
        if(strcmp(bitmapList[i]->fileName, fileName) == 0)
            return bitmapList[i];
    }
    return nullptr;
}
