// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/base.h>

#include <nana/runner/base_types.h>

#include <nana/runner/parser.h>

std::ostream& std::operator<<(ostream& _os, const wstring& _v)
{
    _os << nana::runner::to_string(_v);
    return _os;
}

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

void nana::runner::string_split(const string& _s, std::vector<string>& _ss)
{
    parser ps{ _s, true };
    ps >> _ss;
}

void nana::runner::string_split(const wstring& _s, std::vector<wstring>& _ss)
{
    string u8s;
    u8s << _s;
    parser ps{ u8s, true };
    ps >> _ss;
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
        if (line.size() > 2)
        {
            if (line[0] == '\xef' && line[1] == '\xbb' && line[2] == '\xbf')
                line.erase(0, 3);
        }
        if (line.size() > 0)
            if (line[0] == '\r')
                line.erase(0, 1);
        if (line.size() > 0)
            if (line[line.size() - 1] == '\r')
                line.erase(line.size() - 1, 1);
        if (!line.empty())
        {
            _content += line;
            _content += "\n";
        }
    }
    return true;
}

bool nana::runner::write_file(const wstring& _filename, const string& _content)
{
    std::ofstream ofs{ _filename };
    if (!ofs)
    {
        return false;
    }

    ofs.write("\xef\xbb\xbf", 3);
    istr p{ _content };
    while (p)
    {
        istr line = p.read_until(is_newline);
        p.read(is_newline);
        ofs.write(line.data(), line.size());
        ofs << "\n";
    }
    return true;
}

void nana::runner::init_enums()
{
#define NAR_ENUM_COLOR_ADD(c) NAR_ENUM_ADD(nana::colors, black, c)
    NAR_ENUM_COLOR_ADD(alice_blue);
    NAR_ENUM_COLOR_ADD(antique_white);
    NAR_ENUM_COLOR_ADD(aqua);
    NAR_ENUM_COLOR_ADD(aquamarine);
    NAR_ENUM_COLOR_ADD(azure); 
    NAR_ENUM_COLOR_ADD(beige);
    NAR_ENUM_COLOR_ADD(bisque);
    NAR_ENUM_COLOR_ADD(black);
    NAR_ENUM_COLOR_ADD(blanched_almond);
    NAR_ENUM_COLOR_ADD(blue); 
    NAR_ENUM_COLOR_ADD(blue_violet);
    NAR_ENUM_COLOR_ADD(brown);
    NAR_ENUM_COLOR_ADD(burly_wood);
    NAR_ENUM_COLOR_ADD(cadet_blue);
    NAR_ENUM_COLOR_ADD(chartreuse);
    NAR_ENUM_COLOR_ADD(chocolate);
    NAR_ENUM_COLOR_ADD(coral);
    NAR_ENUM_COLOR_ADD(cornflower_blue);
    NAR_ENUM_COLOR_ADD(cornsilk);
    NAR_ENUM_COLOR_ADD(crimson);
    NAR_ENUM_COLOR_ADD(cyan);
    NAR_ENUM_COLOR_ADD(dark_blue);
    NAR_ENUM_COLOR_ADD(dark_cyan);
    NAR_ENUM_COLOR_ADD(dark_goldenrod);
    NAR_ENUM_COLOR_ADD(dark_gray);
    NAR_ENUM_COLOR_ADD(dark_green);
    NAR_ENUM_COLOR_ADD(dark_grey);
    NAR_ENUM_COLOR_ADD(dark_khaki);
    NAR_ENUM_COLOR_ADD(dark_magenta);
    NAR_ENUM_COLOR_ADD(dark_olive_green);
    NAR_ENUM_COLOR_ADD(dark_orange);
    NAR_ENUM_COLOR_ADD(dark_orchid);
    NAR_ENUM_COLOR_ADD(dark_red);
    NAR_ENUM_COLOR_ADD(dark_salmon);
    NAR_ENUM_COLOR_ADD(dark_sea_green);
    NAR_ENUM_COLOR_ADD(dark_slate_blue);
    NAR_ENUM_COLOR_ADD(dark_slate_gray);
    NAR_ENUM_COLOR_ADD(dark_slate_grey);
    NAR_ENUM_COLOR_ADD(dark_turquoise);
    NAR_ENUM_COLOR_ADD(dark_violet);
    NAR_ENUM_COLOR_ADD(deep_pink);
    NAR_ENUM_COLOR_ADD(deep_sky_blue);
    NAR_ENUM_COLOR_ADD(dim_gray);
    NAR_ENUM_COLOR_ADD(dim_grey);
    NAR_ENUM_COLOR_ADD(dodger_blue);
    NAR_ENUM_COLOR_ADD(firebrick);
    NAR_ENUM_COLOR_ADD(floral_white);
    NAR_ENUM_COLOR_ADD(forest_green);
    NAR_ENUM_COLOR_ADD(fuchsia);
    NAR_ENUM_COLOR_ADD(gainsboro);
    NAR_ENUM_COLOR_ADD(ghost_white);
    NAR_ENUM_COLOR_ADD(gold);
    NAR_ENUM_COLOR_ADD(goldenrod);
    NAR_ENUM_COLOR_ADD(gray);
    NAR_ENUM_COLOR_ADD(green);
    NAR_ENUM_COLOR_ADD(green_yellow);
    NAR_ENUM_COLOR_ADD(grey);
    NAR_ENUM_COLOR_ADD(honeydew);
    NAR_ENUM_COLOR_ADD(hot_pink);
    NAR_ENUM_COLOR_ADD(indian_red);
    NAR_ENUM_COLOR_ADD(indigo);
    NAR_ENUM_COLOR_ADD(ivory);
    NAR_ENUM_COLOR_ADD(khaki);
    NAR_ENUM_COLOR_ADD(lavendar);
    NAR_ENUM_COLOR_ADD(lavender_blush);
    NAR_ENUM_COLOR_ADD(lawn_green);
    NAR_ENUM_COLOR_ADD(lemon_chiffon);
    NAR_ENUM_COLOR_ADD(light_blue);
    NAR_ENUM_COLOR_ADD(light_coral);
    NAR_ENUM_COLOR_ADD(light_cyan);
    NAR_ENUM_COLOR_ADD(light_goldenrod_yellow);
    NAR_ENUM_COLOR_ADD(light_gray);
    NAR_ENUM_COLOR_ADD(light_green);
    NAR_ENUM_COLOR_ADD(light_grey);
    NAR_ENUM_COLOR_ADD(light_pink);
    NAR_ENUM_COLOR_ADD(light_salmon);
    NAR_ENUM_COLOR_ADD(light_sea_green);
    NAR_ENUM_COLOR_ADD(light_sky_blue);
    NAR_ENUM_COLOR_ADD(light_slate_gray);
    NAR_ENUM_COLOR_ADD(light_slate_grey);
    NAR_ENUM_COLOR_ADD(light_steel_blue);
    NAR_ENUM_COLOR_ADD(light_yellow);
    NAR_ENUM_COLOR_ADD(lime);
    NAR_ENUM_COLOR_ADD(lime_green);
    NAR_ENUM_COLOR_ADD(linen);
    NAR_ENUM_COLOR_ADD(magenta);
    NAR_ENUM_COLOR_ADD(maroon);
    NAR_ENUM_COLOR_ADD(medium_aquamarine);
    NAR_ENUM_COLOR_ADD(medium_blue);
    NAR_ENUM_COLOR_ADD(medium_orchid);
    NAR_ENUM_COLOR_ADD(medium_purple);
    NAR_ENUM_COLOR_ADD(medium_sea_green);
    NAR_ENUM_COLOR_ADD(medium_slate_blue);
    NAR_ENUM_COLOR_ADD(medium_spring_green);
    NAR_ENUM_COLOR_ADD(medium_turquoise);
    NAR_ENUM_COLOR_ADD(medium_violet_red);
    NAR_ENUM_COLOR_ADD(midnight_blue);
    NAR_ENUM_COLOR_ADD(mint_cream);
    NAR_ENUM_COLOR_ADD(misty_rose);
    NAR_ENUM_COLOR_ADD(moccasin);
    NAR_ENUM_COLOR_ADD(navajo_white);
    NAR_ENUM_COLOR_ADD(navy);
    NAR_ENUM_COLOR_ADD(old_lace);
    NAR_ENUM_COLOR_ADD(olive);
    NAR_ENUM_COLOR_ADD(olive_drab);
    NAR_ENUM_COLOR_ADD(orange);
    NAR_ENUM_COLOR_ADD(orange_red);
    NAR_ENUM_COLOR_ADD(orchid);
    NAR_ENUM_COLOR_ADD(pale_goldenrod);
    NAR_ENUM_COLOR_ADD(pale_green);
    NAR_ENUM_COLOR_ADD(pale_turquoise);
    NAR_ENUM_COLOR_ADD(pale_violet_red);
    NAR_ENUM_COLOR_ADD(papaya_whip);
    NAR_ENUM_COLOR_ADD(peach_puff);
    NAR_ENUM_COLOR_ADD(peru);
    NAR_ENUM_COLOR_ADD(pink);
    NAR_ENUM_COLOR_ADD(plum);
    NAR_ENUM_COLOR_ADD(powder_blue);
    NAR_ENUM_COLOR_ADD(purple);
    NAR_ENUM_COLOR_ADD(red);
    NAR_ENUM_COLOR_ADD(rosy_brown);
    NAR_ENUM_COLOR_ADD(royal_blue);
    NAR_ENUM_COLOR_ADD(saddle_brown);
    NAR_ENUM_COLOR_ADD(salmon);
    NAR_ENUM_COLOR_ADD(sandy_brown);
    NAR_ENUM_COLOR_ADD(sea_green);
    NAR_ENUM_COLOR_ADD(sea_shell);
    NAR_ENUM_COLOR_ADD(sienna);
    NAR_ENUM_COLOR_ADD(silver);
    NAR_ENUM_COLOR_ADD(sky_blue);
    NAR_ENUM_COLOR_ADD(slate_blue);
    NAR_ENUM_COLOR_ADD(slate_gray);
    NAR_ENUM_COLOR_ADD(slate_grey);
    NAR_ENUM_COLOR_ADD(snow);
    NAR_ENUM_COLOR_ADD(spring_green);
    NAR_ENUM_COLOR_ADD(steel_blue);
    NAR_ENUM_COLOR_ADD(tan);
    NAR_ENUM_COLOR_ADD(teal);
    NAR_ENUM_COLOR_ADD(thistle);
    NAR_ENUM_COLOR_ADD(tomato);
    NAR_ENUM_COLOR_ADD(turquoise);
    NAR_ENUM_COLOR_ADD(violet);
    NAR_ENUM_COLOR_ADD(wheat);
    NAR_ENUM_COLOR_ADD(white);
    NAR_ENUM_COLOR_ADD(white_smoke);
    NAR_ENUM_COLOR_ADD(yellow);
    NAR_ENUM_COLOR_ADD(yellow_green);

    NAR_ENUM_ADD(nana::arrange, unknown, unknown);
    NAR_ENUM_ADD(nana::arrange, unknown, horizontal);
    NAR_ENUM_ADD(nana::arrange, unknown, vertical);
    NAR_ENUM_ADD(nana::arrange, unknown, horizontal_vertical);

    NAR_ENUM_ADD(nana::align, left, left);
    NAR_ENUM_ADD(nana::align, left, center);
    NAR_ENUM_ADD(nana::align, left, right);

    NAR_ENUM_ADD(nana::align_v, top, top);
    NAR_ENUM_ADD(nana::align_v, top, center);
    NAR_ENUM_ADD(nana::align_v, top, bottom);

    NAR_ENUM_ADD(nana::direction, north, north);
    NAR_ENUM_ADD(nana::direction, north, south);
    NAR_ENUM_ADD(nana::direction, north, east);
    NAR_ENUM_ADD(nana::direction, north, west);
    NAR_ENUM_ADD(nana::direction, north, southeast);

    NAR_ENUM_ADD(nana::cursor, arrow, hand);
    NAR_ENUM_ADD(nana::cursor, arrow, arrow);
    NAR_ENUM_ADD(nana::cursor, arrow, wait);
    NAR_ENUM_ADD(nana::cursor, arrow, iterm);
    NAR_ENUM_ADD(nana::cursor, arrow, size_we);
    NAR_ENUM_ADD(nana::cursor, arrow, size_ns);
    NAR_ENUM_ADD(nana::cursor, arrow, size_top_left);
    NAR_ENUM_ADD(nana::cursor, arrow, size_top_right);
    NAR_ENUM_ADD(nana::cursor, arrow, size_bottom_left);
    NAR_ENUM_ADD(nana::cursor, arrow, size_bottom_right);
}

