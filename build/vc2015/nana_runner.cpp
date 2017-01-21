// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "nana_runner.h"

#include <nana/runner/dumper.h>
#include <nana/runner/log.h>
#include <nana/runner/view_cfg.h>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    nana::runner::app app(lpCmdLine);
    return app.go();
}

nana::runner::app::app(const wchar_t* _cmdline)
{
}

int nana::runner::app::go()
{
    using namespace nana;
    using namespace nana::runner;

    form f;
    f.caption("Log Viewer");
    f.div("a");
    nana::textbox l(f);
    f["a"] << l;
    f.collocate();

    l.line_wrapped(true);
    l.bgcolor(colors::black);
    l.fgcolor(color{ "rgb(0,255,0)" });

    set_log_handler([&l](const string& s) {
        write_console(s);
        l.append(s, false);
    });

    log() << "beginning...";

    log() << id{ "a.b[1].c" };

    dumper d;
    d << f.caption();
    log() << d;

    view_cfg cfg{ "root", "hello" };
    cfg.add({"child1", "world1"});
    cfg.add({"child2", "world2"});
    log() << cfg;
    log() << dump(cfg, true);
    for (auto i : cfg.children())
        log() << "child id = " << i.id_name();

    log() << "end.";

    f.show();
    exec();
    return 0;
}

