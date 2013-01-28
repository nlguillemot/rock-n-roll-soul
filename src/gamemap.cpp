#include "gamemap.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace heart
{

bool GameMap::load_from_file(const std::string& filename)
{
    std::cout << "Loading map: " << (filename + ".map")<< std::endl;
    std::ifstream ifs(filename + ".map");
    if (!ifs)
    {
        return false;
    }

    std::vector<Platform> platforms;
    std::vector<Collectible> collectibles;
    std::vector<SpawnPoint> spawnpoints;
    std::vector<GoalFlag> goalflags;
    std::vector<Decoration> decorations;
    PhysicsConfiguration physics;

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

        if (type == "platform")
        {
            Platform plat;

            ss >> plat.asset_name;
            ss >> plat.position.x;
            ss >> plat.position.y;

            platforms.push_back(plat);
        }
        else if (type == "collectible")
        {
            Collectible coll;

            ss >> coll.asset_name;
            ss >> coll.position.x;
            ss >> coll.position.y;

            collectibles.push_back(coll);
        }
        else if (type == "spawnpoint")
        {
            SpawnPoint spawn;

            ss >> spawn.name;
            ss >> spawn.position.x;
            ss >> spawn.position.y;

            spawnpoints.push_back(spawn);
        }
        else if (type == "gravity")
        {
            ss >> physics.gravity.x;
            ss >> physics.gravity.y;
        }
        else if (type == "goal")
        {
            GoalFlag flag;

            ss >> flag.asset_name;
            ss >> flag.position.x;
            ss >> flag.position.y;
            goalflags.push_back(flag);
        }
        else if (type == "decoration")
        {
            Decoration dec;

            ss >> dec.asset_name;
            ss >> dec.position.x;
            ss >> dec.position.y;
            decorations.push_back(dec);
        }
        else
        {
            std::cout << "Unknown type: " << type << std::endl;
        }
    }

    platform_list_.swap(platforms);
    collectible_list_.swap(collectibles);
    spawnpoint_list_.swap(spawnpoints);
    goalflag_list_.swap(goalflags);
    decoration_list_.swap(decorations);
    physics_ = physics;

    return true;
}

const GameMap::SpawnPoint* GameMap::spawnpoint(const std::string& name)
{
    for (const SpawnPoint& sp : spawnpoint_list_)
    {
        if (sp.name == name)
        {
            return &sp;
        }
    }

    return nullptr;
}

const std::vector<GameMap::Platform>& GameMap::platforms() const
{
    return platform_list_;
}

const std::vector<GameMap::GoalFlag>& GameMap::goalflags() const
{
    return goalflag_list_;
}

const std::vector<GameMap::Collectible>& GameMap::collectibles() const
{
    return collectible_list_;
}

const std::vector<GameMap::Decoration>& GameMap::decorations() const
{
    return decoration_list_;
}

const GameMap::PhysicsConfiguration& GameMap::physics() const
{
    return physics_;
}

}
