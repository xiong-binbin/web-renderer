//
// Created by user on 2022/4/26 0026.
//
#include "cef_render.h"
#include "simple_app.h"

CefRender::CefRender(const std::string& url, int width, int height)
        : url(url), width(width), height(height)
{
    // SimpleHandler implements browser-level callbacks.
    handler = CefRefPtr<SimpleHandler>(new SimpleHandler(width, height));
}

CefRender::~CefRender()
{
}

int CefRender::Start()
{
    CefWindowInfo window_info;
    window_info.SetAsWindowless(0);

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;
    // 设置离屏渲染帧率
    browser_settings.windowless_frame_rate = 30;

    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, handler, this->url, browser_settings, nullptr, nullptr);

    return 0;
}

void CefRender::Stop()
{
    handler->CloseAllBrowsers(false);
}

void CefRender::RunMessageLoop()
{
    // Provide CEF with command-line arguments.
    CefMainArgs main_args(0, nullptr);

    // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
    // that share the same executable. This function checks the command-line and,
    // if this is a sub-process, executes the appropriate logic.
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return;
    }

    // Specify CEF global settings here.
    CefSettings settings;
    settings.no_sandbox = true;
    settings.windowless_rendering_enabled = true;
    settings.log_severity = LOGSEVERITY_DISABLE;

    // SimpleApp implements application-level callbacks for the browser process.
    // It will create the first browser instance in OnContextInitialized() after
    // CEF has initialized.
    CefRefPtr<SimpleApp> app(new SimpleApp);

    // Initialize CEF for the browser process.
    CefInitialize(main_args, settings, app.get(), nullptr);

    // Run the CEF message loop. This will block until CefQuitMessageLoop() is
    while (true)
    {
        CefRunMessageLoop();
    }

    // Shut down CEF.
    CefShutdown();
}

