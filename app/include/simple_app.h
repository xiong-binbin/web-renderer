//
// Created by user on 2022/4/26 0026.
//

#ifndef MDC_DIRECTOR_UTILS_SIMPLE_APP_H
#define MDC_DIRECTOR_UTILS_SIMPLE_APP_H


#include <iostream>
#include "include/cef_app.h"

class SimpleApp : public CefApp, public CefBrowserProcessHandler
{
public:
    explicit SimpleApp();
    ~SimpleApp();

    // CefApp methods:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    // CefBrowserProcessHandler methods:
    void OnContextInitialized() override;

    void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(SimpleApp);
};


#endif //MDC_DIRECTOR_UTILS_SIMPLE_APP_H
