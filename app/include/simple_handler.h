//
// Created by user on 2022/4/26 0026.
//

#ifndef MDC_DIRECTOR_UTILS_SIMPLE_HANDLER_H
#define MDC_DIRECTOR_UTILS_SIMPLE_HANDLER_H


#include "include/cef_client.h"
#include <list>
#include <iostream>
#include <functional>


using CefRenderOutputCallback = std::function<void(const void* buffer)>;
using CefRenderErrorCallback  = std::function<void()>;

class SimpleHandler : public CefClient,
                      public CefLifeSpanHandler,
                      public CefLoadHandler,
                      public CefRenderHandler
{
public:
    explicit SimpleHandler(int width, int height);
    ~SimpleHandler();

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override {
        return this;
    }
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override {
        return this;
    }

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString& errorText,
                             const CefString& failedUrl) override;

    // CefRenderHandler methods
    virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                         CefRenderHandler::PaintElementType type,
                         const CefRenderHandler::RectList& dirtyRects,
                         const void* buffer,
                         int width,
                         int height) override;

    // Request that all existing browser windows close.
    void CloseAllBrowsers(bool force_close);

    //注册CEF渲染输出的处理
    inline void SetCefRenderOutputHandler(CefRenderOutputCallback callback) {
        cefRenderOutputCallback = callback;
    }

    //注册CEF渲染错误的处理
    inline void SetCefRenderErrorHandler(CefRenderErrorCallback callback) {
        cefRenderErrorCallback = callback;
    }

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(SimpleHandler);

private:
    int  width{ 0 };
    int  height{ 0 };
    std::list<CefRefPtr<CefBrowser>>  browserList;
    CefRenderOutputCallback  cefRenderOutputCallback{ nullptr };
    CefRenderErrorCallback   cefRenderErrorCallback{ nullptr };
};


#endif //MDC_DIRECTOR_UTILS_SIMPLE_HANDLER_H
