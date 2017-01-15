// nana_runner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "nana_runner.h"

#include <nana/runner/dumper.h>
#include <nana/runner/log.h>
#include <nana/runner/view_cfg.h>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

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

    string s{ "Hello, world!" };
    f.caption(s);

    dumper d;
    d << s;
    log() << d;

    view_cfg cfg;
    cfg.add(id{"child1"});
    cfg.add(id{"child2"});
    log() << cfg;
    for (auto i : cfg.children())
        log() << "child id = " << i.id_name();

    nana::label l(f);
    l.caption(dump(cfg));
    f.div("a");
    f["a"] << l;
    f.collocate();

    f.show();
    exec();
    return 0;
}

