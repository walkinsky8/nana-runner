// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include "nana_runner.h"

#include <nana/runner/base_types.h>

#include <nana/runner/log.h>
#include <nana/runner/dumper.h>
#include <nana/runner/parser.h>

#include <nana/runner/view_cfg.h>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>

using namespace nana;
using namespace nana::runner;

namespace view {

    class Hello
    {
        view_cfg& cfg_;
        form& form_;

        label& label_;
        textbox& world_;
        button& quit_;

    public:
        Hello(view_cfg& _cfg, form& _form)
            : cfg_{ _cfg }, form_{_form}
            , label_{ _cfg.wnd<label>("hello.label") }
            , world_{ _cfg.wnd<textbox>("hello.world") }
            , quit_{ _cfg.wnd<button>("hello.quit") }
        {}

        void show()
        {
            make_form(form_, cfg_);
            form_.show();
        }
    };

}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    nana::runner::app app(lpCmdLine);
    return app.go();
}

nana::runner::app::app(const wchar_t* _cmdline)
    : cmdline_{_cmdline}
{
    initialize();
}

int nana::runner::app::go()
{
    string cfg;
    if (!read_file(cmdline_, cfg))
    {
        log() << "no cfg file";
        return 1;
    }
    //VIO_LOG_VAR(cfg);

    parser parsed(cfg);
    //VIO_LOG_VAR(parsed);

    view_cfg viewcfg;
    //VIO_LOG_VAR(viewcfg);

    parsed >> viewcfg;
    //VIO_LOG_VAR(viewcfg);

    form f;
    viewcfg.make_widgets(f);

    view::Hello hello(viewcfg, f);
    hello.show();
    
    //set_log_handler([&l](const string& s) {
    //    write_console(s);
    //    l.append(s, false);
    //});

    exec();
    return 0;
}

