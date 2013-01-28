#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace heart
{

class MenuLayout
{
public:
    struct LevelButton
    {
        std::string level_name;
        std::string level_icon;
        sf::Vector2f position;
    };

    struct Decoration
    {
        std::string asset_name;
        sf::Vector2f position;
    };

    bool load_from_file(const std::string& filename);

    const std::vector<Decoration>& decorations() const;
    const std::vector<LevelButton>& levelbuttons() const;

private:
    std::vector<Decoration> decoration_list_;
    std::vector<LevelButton> level_buttons_;
};

}
