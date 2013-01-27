#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

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

    struct SpawnPoint
    {
        std::string name;
        sf::Vector2f position;
    };

    struct PhysicsConfiguration
    {
        sf::Vector2f gravity;
    };

    bool load_from_file(const std::string& filename);

    const SpawnPoint* spawnpoint(const std::string& name);

    const std::vector<Platform>& platforms() const;

    const PhysicsConfiguration& physics() const;

private:
    std::vector<Platform> platform_list_;
    std::vector<Collectible> collectible_list_;
    std::vector<SpawnPoint> spawnpoint_list_;

    PhysicsConfiguration physics_;
};

}
