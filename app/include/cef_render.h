//
// Created by user on 2022/4/26 0026.
//

#ifndef MDC_DIRECTOR_UTILS_CEF_RENDER_H
#define MDC_DIRECTOR_UTILS_CEF_RENDER_H

#include <iostream>
#include "simple_handler.h"

class CefRender
{
public:
    CefRender(const std::string& url, int width, int height);
    ~CefRender();

    int  Start();
    void Stop();

    //设置渲染输出的图像的回调处理
    void SetPictureHandler(const std::function<void(const void* buffer)>& callback) {
        handler->SetCefRenderOutputHandler(callback);
    }

    //设置渲染错误的回调处理
    void SetErrorHandler(const std::function<void()>& callback) {
        handler->SetCefRenderErrorHandler(callback);
    }

    //cef消息循环，占用一个线程
    static void RunMessageLoop();

private:
    std::string  url;
    int     width{ 0 };
    int     height{ 0 };
    CefRefPtr<SimpleHandler>  handler;
};

#endif //MDC_DIRECTOR_UTILS_CEF_RENDER_H
