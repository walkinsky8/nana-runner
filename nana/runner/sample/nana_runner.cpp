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
    using namespace runa;
    //try {
        sample::editor_app a;
        //sample::demo_app a;
        a.run(lpCmdLine);
    //}
    //catch (std::exception& e) {
    //    NAR_LOG_EXCPT(e);
    //    return -1;
    //}
    return 0;
}

