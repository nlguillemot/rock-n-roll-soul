#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

namespace heart
{

class GameMap
{
public:
    struct Platform
    {
        std::string asset_name;
        sf::Vector2f position;
    };

    struct Collectible
    {
        std::string type;
        sf::Vector2f position;
    };

    bool load_from_file(const std::string& filename);

    std::list<Platform> platform_list;
    std::list<Collectible> collectible_list;
};

}
