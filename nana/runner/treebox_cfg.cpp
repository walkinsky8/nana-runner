// Created by walkinsky(lyh6188@hotmail.com), 2018/10/20
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "treebox_cfg.h"

#include "option_cfg.h"

void runa::treebox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& tree = dynamic_cast<ui_type&>(_w);

    if (!checkable_().empty())
        tree.checkable(checkable_().value());

    if (!directory_().empty())
    {
        auto node = tree.insert(directory_(), directory_());
        fs::directory_iterator i(directory_()), end;
        for (; i != end; ++i)
        {
            auto name = nana::to_utf8(i->path().filename().native());
            tree.insert(node, name, name);
            break;
        }

        tree.events().expanded([&tree](const nana::arg_treebox& arg)
        {
            if (!arg.operated) return; //If this is contracted.

            //Windows supports the path separator '/'
            auto path = tree.make_key_path(arg.item, "/") + "/";

            //avoids frequent useless refreshing
            tree.auto_draw(false);

            //Walk in the path directory for sub directories.
            for (fs::directory_iterator i{ path }, end; i != end; ++i)
            {
                if (!is_directory(*i)) continue; //If it is not a directory.

                auto name = nana::to_utf8(i->path().filename().native());
                auto child = tree.insert(arg.item, name, name);
                if (child.empty()) continue;

                //Find a directory in child directory, if there is a directory,
                //insert it into the child, just insert one node to indicate the
                //node has a child and an arrow symbol will be?displayed in the
                //front of the node.
                for (fs::directory_iterator u{ path + name }; u != end; ++u)
                {
                    if (!is_directory(*u)) continue; //If it is not a directory.
                    auto name = nana::to_utf8(u->path().filename().native());
                    tree.insert(child, name, name);
                    break;
                }
            }
            tree.auto_draw(true);
        });
        return;
    }

    for (auto& i : children_())
    {
        auto& cfg = i->cast<option_cfg>();
        auto node = tree.insert(cfg.id_path(), cfg.get_caption());
        if (!cfg.children_().empty())
        {
            init_nodes(tree, node, cfg);
        }
    }
}

void runa::treebox_cfg::init_nodes(treebox& _w, item_proxy _p, option_cfg& _c)
{
    for (auto& i : _c.children_())
    {
        auto& c = i->cast<option_cfg>();
        auto p = _w.insert(_p, c.id_path(), c.get_caption());
        if (!c.children_().empty())
        {
            init_nodes(_w, p, c);
        }
    }
}

#endif

