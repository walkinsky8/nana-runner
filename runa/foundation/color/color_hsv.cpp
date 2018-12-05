// Created by walkinsky(lyh6188@hotmail.com), 2018/12/01
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_hsv.h>

#include <runa/foundation/color/color_hsl.h>

#include <runa/foundation/color/color_rgb.h>

namespace runa
{
    color_hsv::color_hsv(nana::color const& c)
    {
        const double r = c.r() / 255.0;
        const double g = c.g() / 255.0;
        const double b = c.b() / 255.0;
        const double maxV = max_(r, g, b);
        const double minV = min_(r, g, b);
        const double diff_max_min = maxV - minV;

        if (diff_max_min == 0.0)
            h_ = 0.0;
        else if (maxV == r)
        {
            h_ = 60.0*(g - b) / diff_max_min;
            if (h_ < 0)
                h_ += 360.0;
        }
        else if (maxV == g)
            h_ = 60.0*(b - r) / diff_max_min + 120.0;
        else if (maxV == b)
            h_ = 60.0*(r - g) / diff_max_min + 240.0;
        else
        {
            assert(false);
        }

        if (maxV==0)
            s_ = 0.0;
        else
            s_ = diff_max_min / maxV;

        v_ = maxV;
    }
    
    nana::color color_hsv::to_color() const
    {
        const int h_i = static_cast<int>(h_ / 60);
        const double f = h_ / 60 - h_i;
        const double p = v_ * (1 - s_);
        const double q = v_ * (1 - f * s_);
        const double t = v_ * (1 - (1 - f)*s_);
        switch (h_i)
        {
        case 0:
            return make_rgb(v_, t, p);
        case 1:
            return make_rgb(q, v_, p);
        case 2:
            return make_rgb(p, v_, t);
        case 3:
            return make_rgb(p, q, v_);
        case 4:
            return make_rgb(t, p, v_);
        case 5:
            return make_rgb(v_, p, q);
        }
        return {};
    }

    string color_hsv::str() const
    {
        std::ostringstream oss;
        oss << "hsv(" << int(h() + 0.5);
        oss << ", " << int((s() + 0.005) * 100) << "%";
        oss << ", " << int((v() + 0.005) * 100) << "%";
        oss << ")";
        return oss.str();
    }

    std::string read_number(std::string& str, std::size_t& pos)
    {
        pos = str.find_first_of("0123456789", pos);
        if (pos == str.npos)
            return{};

        auto end = str.find_first_not_of("0123456789", pos + 1);
        //integer part
        if (end == str.npos)
        {
            pos = end;
            return str.substr(pos);
        }

        if (str[end] == '.')
        {
            auto decimal_end = str.find_first_not_of("0123456789", end + 1);
            if ((decimal_end == str.npos) || (decimal_end == end + 1)) //Because of missing %
                return{};

            end = decimal_end;
        }

        auto ch = str[end];
        if (ch == '%' || ch == ' ' || ch == ',' || ch == ')')
        {
            auto start = pos;
            pos = end + (ch == '%' ? 1 : 0);
            return str.substr(start, pos - start);
        }
        return{};
    }

    color_hsv::color_hsv(const string& _s)
    {
        string css_color = _s;

        const char * excpt_what = "color: invalid hsv format";

        auto pos = css_color.find_first_not_of(' ');
        if (pos == css_color.npos)
            throw std::invalid_argument(excpt_what);

        if ('#' == css_color[pos])
        {
            if (css_color.size() < pos + 4)
                throw std::invalid_argument(excpt_what);

            auto endpos = css_color.find_first_not_of("0123456789abcdefABCDEF", pos + 1);
            if (endpos == css_color.npos)
                endpos = static_cast<decltype(endpos)>(css_color.size());

            if ((endpos - pos != 4) && (endpos - pos != 7))
                throw std::invalid_argument(excpt_what);

            auto n = std::stoi(css_color.substr(pos + 1, endpos - pos - 1), nullptr, 16);

            uint r, g, b;
            if (endpos - pos == 4)
            {
                r = ((0xF00 & n) >> 4) | ((0xF00 & n) >> 8);
                g = (0xF0 & n) | ((0xF0 & n) >> 4);
                b = (0xF & n) | ((0xF & n) << 4);
            }
            else
            {
                r = (0xFF0000 & n) >> 16;
                g = (0xFF00 & n) >> 8;
                b = (0xFF & n);
            }

            *this = color{ r,g,b };
            return;
        }

        //std::tolower is not allowed because of concept requirements
        std::transform(css_color.begin(), css_color.end(), css_color.begin(), [](char ch) {
            if ('A' <= ch && ch <= 'Z')
                return static_cast<char>(ch - ('A' - 'a'));
            return ch;
        });
        auto endpos = css_color.find(' ', pos + 1);
        if (endpos == css_color.npos)
            endpos = css_color.size();

        if ((endpos - pos == 11) && (css_color.substr(pos, 11) == "transparent"))
        {
            *this = color{};
            return;
        }

        auto type_end = css_color.find_first_of(" (", pos + 1);

        if (type_end == css_color.npos || ((type_end - pos != 3) && (type_end - pos != 4)))	//rgb/hsl = 3, rgba/hsla = 4
            throw std::invalid_argument(excpt_what);

        bool has_alpha = false;
        if (type_end - pos == 4) //maybe rgba/hsla
        {
            if (css_color[pos + 3] != 'a')
                throw std::invalid_argument(excpt_what);
            has_alpha = true;
        }

        auto type_name = css_color.substr(pos, 3);
        pos = css_color.find_first_not_of(' ', type_end);
        if (pos == css_color.npos || css_color[pos] != '(')
            throw std::invalid_argument(excpt_what);

        auto str = read_number(css_color, ++pos);
        if (str.empty())
            throw std::invalid_argument(excpt_what);

        if ("rgb" == type_name)
        {
            std::vector<std::string> rgb;

            rgb.emplace_back(std::move(str));
            const bool is_real = (rgb.back().back() == '%');

            for (int i = 0; i < 2; ++i)
            {
                pos = css_color.find_first_not_of(' ', pos);
                if (pos == css_color.npos || css_color[pos] != ',')
                    throw std::invalid_argument(excpt_what);

                str = read_number(css_color, ++pos);
                if (str.empty())
                    throw std::invalid_argument(excpt_what);

                rgb.emplace_back(std::move(str));
                if (rgb.size() == 3)
                    break;
            }

            if (rgb.size() != 3)
                throw std::invalid_argument(excpt_what);

            double r, g, b;
            if (is_real)
            {
                auto pr = std::stod(rgb[0].substr(0, rgb[0].size() - 1));
                r = (pr > 100 ? 255.0 : 2.55 * pr);

                pr = std::stod(rgb[1].substr(0, rgb[1].size() - 1));
                g = (pr > 100 ? 255.0 : 2.55 * pr);

                pr = std::stod(rgb[2].substr(0, rgb[2].size() - 1));
                b = (pr > 100 ? 255.0 : 2.55 * pr);
            }
            else
            {
                r = std::stod(rgb[0]);
                if (r > 255.0)	r = 255;

                g = std::stod(rgb[1]);
                if (g > 255.0)	g = 255;

                b = std::stod(rgb[2]);
                if (b > 255.0)	b = 255;
            }
            *this = (color)color_rgb{ r, g, b };
        }
        else if ("hsl" == type_name)
        {
            if (str.back() == '%')
                throw std::invalid_argument(excpt_what);

            auto h = std::stod(str);

            pos = css_color.find_first_not_of(' ', pos);
            if (pos == css_color.npos || css_color[pos] != ',')
                throw std::invalid_argument(excpt_what);

            str = read_number(css_color, ++pos);
            if (str.empty() || str.back() != '%')
                throw std::invalid_argument(excpt_what);

            auto s = std::stod(str.substr(0, str.size() - 1));

            pos = css_color.find_first_not_of(' ', pos);
            if (pos == css_color.npos || css_color[pos] != ',')
                throw std::invalid_argument(excpt_what);

            str = read_number(css_color, ++pos);
            if (str.empty() || str.back() != '%')
                throw std::invalid_argument(excpt_what);

            auto l = std::stod(str.substr(0, str.size() - 1));

            *this = (color)color_hsl{ h, s / 100, l / 100 };
        }
        else if ("hsv" == type_name)
        {
            if (str.back() == '%')
                throw std::invalid_argument(excpt_what);

            auto h = std::stod(str);

            pos = css_color.find_first_not_of(' ', pos);
            if (pos == css_color.npos || css_color[pos] != ',')
                throw std::invalid_argument(excpt_what);

            str = read_number(css_color, ++pos);
            if (str.empty() || str.back() != '%')
                throw std::invalid_argument(excpt_what);

            auto s = std::stod(str.substr(0, str.size() - 1));

            pos = css_color.find_first_not_of(' ', pos);
            if (pos == css_color.npos || css_color[pos] != ',')
                throw std::invalid_argument(excpt_what);

            str = read_number(css_color, ++pos);
            if (str.empty() || str.back() != '%')
                throw std::invalid_argument(excpt_what);

            auto v = std::stod(str.substr(0, str.size() - 1));

            *this = color_hsv{ h, s / 100, v / 100 };
        }
        else
            throw std::invalid_argument(excpt_what);	//invalid color type

        if (has_alpha)
        {
            str = read_number(css_color, ++pos);
            if (str.empty() || str.back() == '%')
                throw std::invalid_argument(excpt_what); //invalid alpha value

            *this = ((color)*this).alpha(std::stod(str));
        }
    }

}//end namespace runa

#endif //__NANA_RUNNER_LIB_ALL_IN_ONE

