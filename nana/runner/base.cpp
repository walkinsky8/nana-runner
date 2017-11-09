// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/base.h>

#include <nana/runner/base_types.h>

std::string& std::operator<<(std::string& _s, const std::wstring& _v)
{
    return _s << nana::to_utf8(_v);
}

std::string& std::operator<<(std::string& _s, const wchar_t* _v)
{
    return _s << std::wstring(_v);
}

void std::operator >> (const std::string& _s, std::wstring& _v)
{
    _v = nana::to_wstring(_s);
}

std::string nana::runner::to_string(const wstring& _wstr)
{
    return nana::to_utf8(_wstr);
}

std::wstring nana::runner::to_wstring(const string& _utf8str)
{
    return nana::to_wstring(_utf8str);
}

bool nana::runner::read_file(const wstring& _filename, string& _content)
{
    std::ifstream ifs{ _filename };
    if (!ifs)
    {
        return false;
    }

    string line;
    while (ifs)
    {
        std::getline(ifs, line);
        _content += line;
        _content += "\n";
    }
    return true;
}

void nana::runner::initialize()
{
#define VIO_ENUM_COLOR_ADD(c) VIO_ENUM_ADD(nana::colors, black, c)
    VIO_ENUM_COLOR_ADD(alice_blue);
    VIO_ENUM_COLOR_ADD(antique_white);
    VIO_ENUM_COLOR_ADD(aqua);
    VIO_ENUM_COLOR_ADD(aquamarine);
    VIO_ENUM_COLOR_ADD(azure); 
    VIO_ENUM_COLOR_ADD(beige);
    VIO_ENUM_COLOR_ADD(bisque);
    VIO_ENUM_COLOR_ADD(black);
    VIO_ENUM_COLOR_ADD(blanched_almond);
    VIO_ENUM_COLOR_ADD(blue); 
    VIO_ENUM_COLOR_ADD(blue_violet);
    VIO_ENUM_COLOR_ADD(brown);
    VIO_ENUM_COLOR_ADD(burly_wood);
    VIO_ENUM_COLOR_ADD(cadet_blue);
    VIO_ENUM_COLOR_ADD(chartreuse);
    VIO_ENUM_COLOR_ADD(chocolate);
    VIO_ENUM_COLOR_ADD(coral);
    VIO_ENUM_COLOR_ADD(cornflower_blue);
    VIO_ENUM_COLOR_ADD(cornsilk);
    VIO_ENUM_COLOR_ADD(crimson);
    VIO_ENUM_COLOR_ADD(cyan);
    VIO_ENUM_COLOR_ADD(dark_blue);
    VIO_ENUM_COLOR_ADD(dark_cyan);
    VIO_ENUM_COLOR_ADD(dark_goldenrod);
    VIO_ENUM_COLOR_ADD(dark_gray);
    VIO_ENUM_COLOR_ADD(dark_green);
    VIO_ENUM_COLOR_ADD(dark_grey);
    VIO_ENUM_COLOR_ADD(dark_khaki);
    VIO_ENUM_COLOR_ADD(dark_magenta);
    VIO_ENUM_COLOR_ADD(dark_olive_green);
    VIO_ENUM_COLOR_ADD(dark_orange);
    VIO_ENUM_COLOR_ADD(dark_orchid);
    VIO_ENUM_COLOR_ADD(dark_red);
    VIO_ENUM_COLOR_ADD(dark_salmon);
    VIO_ENUM_COLOR_ADD(dark_sea_green);
    VIO_ENUM_COLOR_ADD(dark_slate_blue);
    VIO_ENUM_COLOR_ADD(dark_slate_gray);
    VIO_ENUM_COLOR_ADD(dark_slate_grey);
    VIO_ENUM_COLOR_ADD(dark_turquoise);
    VIO_ENUM_COLOR_ADD(dark_violet);
    VIO_ENUM_COLOR_ADD(deep_pink);
    VIO_ENUM_COLOR_ADD(deep_sky_blue);
    VIO_ENUM_COLOR_ADD(dim_gray);
    VIO_ENUM_COLOR_ADD(dim_grey);
    VIO_ENUM_COLOR_ADD(dodger_blue);
    VIO_ENUM_COLOR_ADD(firebrick);
    VIO_ENUM_COLOR_ADD(floral_white);
    VIO_ENUM_COLOR_ADD(forest_green);
    VIO_ENUM_COLOR_ADD(fuchsia);
    VIO_ENUM_COLOR_ADD(gainsboro);
    VIO_ENUM_COLOR_ADD(ghost_white);
    VIO_ENUM_COLOR_ADD(gold);
    VIO_ENUM_COLOR_ADD(goldenrod);
    VIO_ENUM_COLOR_ADD(gray);
    VIO_ENUM_COLOR_ADD(green);
    VIO_ENUM_COLOR_ADD(green_yellow);
    VIO_ENUM_COLOR_ADD(grey);
    VIO_ENUM_COLOR_ADD(honeydew);
    VIO_ENUM_COLOR_ADD(hot_pink);
    VIO_ENUM_COLOR_ADD(indian_red);
    VIO_ENUM_COLOR_ADD(indigo);
    VIO_ENUM_COLOR_ADD(ivory);
    VIO_ENUM_COLOR_ADD(khaki);
    VIO_ENUM_COLOR_ADD(lavendar);
    VIO_ENUM_COLOR_ADD(lavender_blush);
    VIO_ENUM_COLOR_ADD(lawn_green);
    VIO_ENUM_COLOR_ADD(lemon_chiffon);
    VIO_ENUM_COLOR_ADD(light_blue);
    VIO_ENUM_COLOR_ADD(light_coral);
    VIO_ENUM_COLOR_ADD(light_cyan);
    VIO_ENUM_COLOR_ADD(light_goldenrod_yellow);
    VIO_ENUM_COLOR_ADD(light_gray);
    VIO_ENUM_COLOR_ADD(light_green);
    VIO_ENUM_COLOR_ADD(light_grey);
    VIO_ENUM_COLOR_ADD(light_pink);
    VIO_ENUM_COLOR_ADD(light_salmon);
    VIO_ENUM_COLOR_ADD(light_sea_green);
    VIO_ENUM_COLOR_ADD(light_sky_blue);
    VIO_ENUM_COLOR_ADD(light_slate_gray);
    VIO_ENUM_COLOR_ADD(light_slate_grey);
    VIO_ENUM_COLOR_ADD(light_steel_blue);
    VIO_ENUM_COLOR_ADD(light_yellow);
    VIO_ENUM_COLOR_ADD(lime);
    VIO_ENUM_COLOR_ADD(lime_green);
    VIO_ENUM_COLOR_ADD(linen);
    VIO_ENUM_COLOR_ADD(magenta);
    VIO_ENUM_COLOR_ADD(maroon);
    VIO_ENUM_COLOR_ADD(medium_aquamarine);
    VIO_ENUM_COLOR_ADD(medium_blue);
    VIO_ENUM_COLOR_ADD(medium_orchid);
    VIO_ENUM_COLOR_ADD(medium_purple);
    VIO_ENUM_COLOR_ADD(medium_sea_green);
    VIO_ENUM_COLOR_ADD(medium_slate_blue);
    VIO_ENUM_COLOR_ADD(medium_spring_green);
    VIO_ENUM_COLOR_ADD(medium_turquoise);
    VIO_ENUM_COLOR_ADD(medium_violet_red);
    VIO_ENUM_COLOR_ADD(midnight_blue);
    VIO_ENUM_COLOR_ADD(mint_cream);
    VIO_ENUM_COLOR_ADD(misty_rose);
    VIO_ENUM_COLOR_ADD(moccasin);
    VIO_ENUM_COLOR_ADD(navajo_white);
    VIO_ENUM_COLOR_ADD(navy);
    VIO_ENUM_COLOR_ADD(old_lace);
    VIO_ENUM_COLOR_ADD(olive);
    VIO_ENUM_COLOR_ADD(olive_drab);
    VIO_ENUM_COLOR_ADD(orange);
    VIO_ENUM_COLOR_ADD(orange_red);
    VIO_ENUM_COLOR_ADD(orchid);
    VIO_ENUM_COLOR_ADD(pale_goldenrod);
    VIO_ENUM_COLOR_ADD(pale_green);
    VIO_ENUM_COLOR_ADD(pale_turquoise);
    VIO_ENUM_COLOR_ADD(pale_violet_red);
    VIO_ENUM_COLOR_ADD(papaya_whip);
    VIO_ENUM_COLOR_ADD(peach_puff);
    VIO_ENUM_COLOR_ADD(peru);
    VIO_ENUM_COLOR_ADD(pink);
    VIO_ENUM_COLOR_ADD(plum);
    VIO_ENUM_COLOR_ADD(powder_blue);
    VIO_ENUM_COLOR_ADD(purple);
    VIO_ENUM_COLOR_ADD(red);
    VIO_ENUM_COLOR_ADD(rosy_brown);
    VIO_ENUM_COLOR_ADD(royal_blue);
    VIO_ENUM_COLOR_ADD(saddle_brown);
    VIO_ENUM_COLOR_ADD(salmon);
    VIO_ENUM_COLOR_ADD(sandy_brown);
    VIO_ENUM_COLOR_ADD(sea_green);
    VIO_ENUM_COLOR_ADD(sea_shell);
    VIO_ENUM_COLOR_ADD(sienna);
    VIO_ENUM_COLOR_ADD(silver);
    VIO_ENUM_COLOR_ADD(sky_blue);
    VIO_ENUM_COLOR_ADD(slate_blue);
    VIO_ENUM_COLOR_ADD(slate_gray);
    VIO_ENUM_COLOR_ADD(slate_grey);
    VIO_ENUM_COLOR_ADD(snow);
    VIO_ENUM_COLOR_ADD(spring_green);
    VIO_ENUM_COLOR_ADD(steel_blue);
    VIO_ENUM_COLOR_ADD(tan);
    VIO_ENUM_COLOR_ADD(teal);
    VIO_ENUM_COLOR_ADD(thistle);
    VIO_ENUM_COLOR_ADD(tomato);
    VIO_ENUM_COLOR_ADD(turquoise);
    VIO_ENUM_COLOR_ADD(violet);
    VIO_ENUM_COLOR_ADD(wheat);
    VIO_ENUM_COLOR_ADD(white);
    VIO_ENUM_COLOR_ADD(white_smoke);
    VIO_ENUM_COLOR_ADD(yellow);
    VIO_ENUM_COLOR_ADD(yellow_green);
}
