#include "menulayout.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace heart
{

bool MenuLayout::load_from_file(const std::string& filename)
{
    std::ifstream ifs(filename + ".menu");
    if (!ifs)
    {
        return false;
    }

    std::vector<Decoration> decs;
    std::vector<LevelButton> levelbuttons;

    std::string line;

    while (std::getline(ifs,line))
    {
        std::stringstream ss;
        ss << line;

        size_t hashindx = line.find('#');
        if (hashindx != std::string::npos)
        {
            line = line.substr(0,hashindx);
        }

        if (line.empty())
            continue;

        std::string type;
        ss >> type;

        if (type == "level")
        {
            LevelButton but;
            ss >> but.level_name;
            ss >> but.level_icon;
            ss >> but.position.x;
            ss >> but.position.y;
            levelbuttons.push_back(but);
        }
        else if (type == "decoration")
        {
            Decoration dec;

            ss >> dec.asset_name;
            ss >> dec.position.x;
            ss >> dec.position.y;
            decs.push_back(dec);
        }
        else
        {
            std::cout << "Unknown type: " << type << std::endl;
        }
    }

    decoration_list_.swap(decs);
    level_buttons_.swap(levelbuttons);

    return true;
}

const std::vector<MenuLayout::Decoration>& MenuLayout::decorations() const
{
    return decoration_list_;
}

const std::vector<MenuLayout::LevelButton>& MenuLayout::levelbuttons() const
{
    return level_buttons_;
}

}
