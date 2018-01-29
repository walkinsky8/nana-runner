// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include "app_base.h"

#include <nana/runner/view_factory.h>

#include <nana/runner/log_viewer_view.h>
#include <nana/runner/login_view.h>
#include <nana/runner/hello_view.h>
#include <nana/runner/demo_view.h>
#include <nana/runner/font_view.h>
#include <nana/runner/color_view.h>

using namespace nana::runner;
using namespace nana::runner::view;

class Runner : public app_base
{
    LogViewer* log_{};
    Login* login_{};
    Demo* demo_{};

public:
    void init_views() override
    {
        add_view<LogViewer>();
        add_view<Login>();
        add_view<Hello>();
        add_view<Demo>();
        add_view<Font>();
        add_view<Color>();
    }

    void init_logic() override
    {
        log_ = get_view<LogViewer>();
        login_ = get_view<Login>();
        demo_ = get_view<Demo>();

        log_->show();
        login_->show();
        login_->on_login([this] {
            demo_->show();
        });
    }

};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Runner r;
    r.run(lpCmdLine);
    return 0;
}
