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

void PictureHandler(const void* buffer)
{
    printf("%s_%d: -------------------- \n", __FILE__, __LINE__);
}

int main(int argc, char *argv[])
{
    std::thread thread([&](){
        sleep(3);
        CefRender cr("https://www.ithome.com/", 1280, 720);
        cr.SetPictureHandler(PictureHandler);
        cr.Start();
        pause();
    });
    thread.detach();

    CefRender::RunMessageLoop();

    return 0;
}