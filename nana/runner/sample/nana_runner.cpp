// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include <nana/runner/app_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/sample/log_viewer_view.h>
#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/editor_view.h>

#include <nana/runner/sample/hello_view.h>
#include <nana/runner/sample/demo_view.h>
#include <nana/runner/sample/font_view.h>
#include <nana/runner/sample/color_view.h>

namespace nana::runner::sample {

    using namespace view;

    class app : public app_base
    {
        LogViewer* log_{};
        Login* login_{};
        Editor* editor_{};

    public:
        void init_views() override
        {
            add_view<LogViewer>();
            add_view<Login>();
            add_view<Editor>();
            add_view<Hello>();
            add_view<Demo>();
            add_view<Font>();
            add_view<Color>();
        }

        void init_logic() override
        {
            log_ = get_view<LogViewer>();
            login_ = get_view<Login>();
            editor_ = get_view<Editor>();

            log_->show();
            login_->show();
            login_->on_login([this] {
                editor_->show();
            });
        }

    };

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    nana::runner::sample::app a;
    a.run(lpCmdLine);
    return 0;
}
