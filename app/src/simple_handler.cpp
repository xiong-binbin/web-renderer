//
// Created by user on 2022/4/26 0026.
//
#include "simple_handler.h"
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_parser.h"
#include "include/base/cef_callback.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"


SimpleHandler::SimpleHandler(int width, int height)
        : width(width), height(height)
{
}

SimpleHandler::~SimpleHandler()
{
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    this->browserList.push_back(browser);
}

bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
    return false;
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    for(auto iter = this->browserList.begin(); iter != this->browserList.end(); iter++)
    {
        if((*iter)->IsSame(browser))
        {
            this->browserList.erase(iter);
            break;
        }
    }

    if(this->browserList.empty())
    {
        CefQuitMessageLoop();
    }
}

void SimpleHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                ErrorCode errorCode,
                                const CefString& errorText,
                                const CefString& failedUrl)
{
    if(this->cefRenderErrorCallback) {
        auto callback = this->cefRenderErrorCallback;
        callback();
    }
    std::cout << "cef OnLoadError" << std::endl;
}

void SimpleHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    // 设置渲染图片的宽高
    rect.x = 0;
    rect.y = 0;
    rect.width = this->width;
    rect.height = this->height;
}

void SimpleHandler::OnPaint(CefRefPtr<CefBrowser> browser,
                            CefRenderHandler::PaintElementType type,
                            const CefRenderHandler::RectList& dirtyRects,
                            const void* buffer,
                            int width,
                            int height)
{
    if(this->cefRenderOutputCallback && width == this->width && height == this->height) {
        auto callback = this->cefRenderOutputCallback;
        callback(buffer);
    }
    else {
        std::cout << "OnPaint Error!" << std::endl;
    }
}

void SimpleHandler::CloseAllBrowsers(bool force_close)
{
    for(auto iter = this->browserList.begin(); iter != this->browserList.end(); iter++)
    {
        (*iter)->GetHost()->CloseBrowser(force_close);
    }
}