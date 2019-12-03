//
//  bmp.hpp
//  openGLTest
//
//  Created by Liunx on 2019. 12. 3..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef bmp_hpp
#define bmp_hpp

#include <stdio.h>

typedef unsigned char       byte;
typedef unsigned long       DWORD;
typedef unsigned short      WORD;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    long  biWidth;
    long  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    long  biXPelsPerMeter;
    long  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    byte rgbBlue;
    byte rgbGreen;
    byte rgbRed;
    byte rgbReserved;
} RGBQUAD;


typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[1];
} BITMAPINFO, *PBITMAPINFO;



class AUX_RGBImageRec {
    void convertBGRtoRGB();
public:
    byte *data;
    DWORD sizeX;
    DWORD sizeY;
    bool NoErrors;
    AUX_RGBImageRec(): NoErrors(false), data(NULL) {};
    AUX_RGBImageRec(const char *FileName);
    ~AUX_RGBImageRec();
    bool loadFile(const char *FileName);
    friend AUX_RGBImageRec *auxDIBImageLoad(const char *FileName);
};


#endif /* bmp_hpp */
