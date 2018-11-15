// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include <nana/runner/sample/editor_app.h>
#include <nana/runner/sample/demo_app.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //nana::runner::sample::editor_app a;
    nana::runner::sample::demo_app a;
    try {
        a.run(lpCmdLine);
    }
    catch (std::exception& e) {
        nana::runner::write_console(std::string{ "exception: " } + e.what());
        return -1;
    }
    return 0;
}
  