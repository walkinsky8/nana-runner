/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
#include "stdafx.h"

#include <runa/foundation/app_base.h>

class nana_runner_app : public runa::app
{
public:
    void on_init() override
    {
        if (!cmdargs().arguments().size())
        {
            NAR_LOG_ERROR("No .nar file specified");
        }
    }

};

// x.nar ... -path "$(RUNA)\runa\foundation" -path "$(RUNA)\runa\sample" -path "$(RUNA)\runa\editor" -path "$(USERPROFILE)\Pictures"

int run_main(runa::pcwstr _cmdline)
{
    nana_runner_app a;
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
#if 1//def _DEBUG
    return run_main(lpCmdLine);
#else
    return run_main_no_exception(lpCmdLine);
#endif
}

