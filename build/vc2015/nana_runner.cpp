// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include "nana_runner.h"

#include <nana/runner/view_cfg.h>

using namespace nana;
using namespace nana::runner;

namespace view {

    class Hello
    {
        view_cfg& cfg_;
        form& form_;

        label& world_;
        textbox& log_;
        button& quit_;

    public:
        Hello(view_cfg& _cfg, form& _form)
            : cfg_{ _cfg }, form_{_form}
            , world_{ _cfg.wnd<label>("hello.world") }
            , log_{ _cfg.wnd<textbox>("hello.log") }
            , quit_{ _cfg.wnd<button>("hello.quit") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                log_.append(s, false);
            });

            quit_.events().click([this] { form_.close(); });
        }

    };

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    nana::runner::app<view::Hello> app(lpCmdLine);
}

