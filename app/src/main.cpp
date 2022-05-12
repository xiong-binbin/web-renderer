/*
 * @Author: your name
 * @Date: 2022-01-13 14:14:11
 * @LastEditTime: 2022-01-13 14:25:27
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /mdc-rtc-osr/app/src/main.cpp
 */
#include <iostream>
#include <unistd.h>
#include <thread>
#include "cef_render.h"

typedef unsigned char   BYTE;
typedef unsigned short	WORD;
typedef unsigned int    DWORD;

typedef struct tagBITMAPFILEHEADER{
    WORD     bfType;        //Linux此值为固定值，0x4d42
    DWORD    bfSize;        //BMP文件的大小，包含三部分
    WORD     bfReserved;    //置0
    WORD     bfReserved2;   //保留，0
    DWORD    bfOffBits;     //文件起始位置到图像像素数据的字节偏移量
}__attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
    DWORD    biSize;          //文件信息头的大小，40
    DWORD    biWidth;         //图像宽度
    DWORD    biHeight;        //图像高度
    WORD     biPlanes;        //BMP存储RGB数据，总为1
    WORD     biBitCount;      //图像像素位数，笔者RGB位数使用24
    DWORD    biCompression;   //压缩 0：不压缩  1：RLE8 2：RLE4
    DWORD    biSizeImage;     //4字节对齐的图像数据大小
    DWORD    biXPelsPerMeter; //水平分辨率  像素/米
    DWORD    biYPelsPerMeter; //垂直分辨率  像素/米
    DWORD    biClrUsed;       //实际使用的调色板索引数，0：使用所有的调色板索引
    DWORD    biClrImportant;
}__attribute__((packed)) BITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;

void SaveImage(int width, int height, const void* buffer, const char* path)
{
    //Set BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = 0;
    bi.biSizeImage = ((width*height) <<2);
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    //Set BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    bf.bfType = 0x4d42;
    bf.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + bi.biSizeImage;
    bf.bfReserved = 0;
    bf.bfReserved2 = 0;
    bf.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    FILE* fp;
    if((fp = fopen(path, "wb")) == NULL)
        return;

    fwrite(&bf,sizeof(BITMAPFILEHEADER),1,fp);        //写入文件头
    fwrite(&bi,sizeof(BITMAPINFOHEADER),1,fp);        //写入信息头
    fwrite(buffer,bi.biSizeImage,1,fp);               //写入图像数据
    fclose(fp);
}

#define  PICTURE_WIDTH   (1280)
#define  PICTURE_HEIGHT  (720)

void PictureHandler(const void* buffer)
{
    static int i = 0;
    std::string name = "picture/" + std::to_string(i) + ".bmp";
    SaveImage(PICTURE_WIDTH, PICTURE_HEIGHT, buffer, name.c_str());
    i++;
}

int main(int argc, char *argv[])
{
    //创建图片文件夹
    system("mkdir -p picture");

    std::thread thread([&](){
        sleep(1);
        CefRender cr("https://www.ithome.com/", PICTURE_WIDTH, PICTURE_HEIGHT);
        cr.SetPictureHandler(PictureHandler);
        cr.Start();
        pause();
    });
    thread.detach();

    CefRender::RunMessageLoop();

    return 0;
}