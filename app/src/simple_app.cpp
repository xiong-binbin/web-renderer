//
// Created by user on 2022/4/26 0026.
//
#include "simple_app.h"
#include "simple_handler.h"
#include "include/wrapper/cef_helpers.h"

SimpleApp::SimpleApp()
{
}

SimpleApp::~SimpleApp()
{
}

void SimpleApp::OnContextInitialized()
{
}

void SimpleApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
    command_line->AppendSwitch("single-process");
    command_line->AppendSwitch("disable-gpu");
    command_line->AppendSwitch("disable-gpu-compositing");
    command_line->AppendSwitch("enable-begin-frame-scheduling");
    command_line->AppendSwitch("enable-system-flash");
    command_line->AppendSwitch("no-zygote");
}
