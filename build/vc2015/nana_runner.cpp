// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include "nana_runner.h"

#include <nana/runner/view_factory.h>

#include <nana/runner/hello_view.h>
#include <nana/runner/demo_view.h>
#include <nana/runner/font_view.h>
#include <nana/runner/color_view.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    using namespace nana::runner;

    add_view<view::Hello>();
    add_view<view::Demo>();
    add_view<view::Font>();
    add_view<view::Color>();

    app a(lpCmdLine);
}
