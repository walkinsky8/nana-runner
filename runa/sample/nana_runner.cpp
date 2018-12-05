// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include <runa/editor/editor_app.h>
#include <runa/sample/demo_app.h>

int run_main(runa::pcwstr _cmdline)
{
    //runa::editor::editor_app a;
    runa::sample::demo_app a;
    a.run(_cmdline);
    return 0;
}

int run_main_no_exception(runa::pcwstr _cmdline)
{
    try {
        return run_main(_cmdline);
    }
    catch (std::exception& e) {
        NAR_LOG_EXCPT(e);
    }
    return -1;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
#ifdef _DEBUG
    return run_main(lpCmdLine);
#else
    return run_main_no_exception(lpCmdLine);
#endif
}

