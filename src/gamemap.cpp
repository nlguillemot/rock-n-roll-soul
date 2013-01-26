#include "gamemap.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace heart
{

bool GameMap::load_from_file(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        return false;
    }

    std::list<Platform> platforms;
    std::list<Collectible> collectibles;

    std::string line;

    while (std::getline(ifs,line))
    {
        std::stringstream ss;
        ss << line;

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

            ss >> coll.type;
            ss >> coll.position.x;
            ss >> coll.position.y;

            collectibles.push_back(coll);
        }
        else
        {
            std::cout << "Unknown type: " << type << std::endl;
        }
    }

    platform_list.swap(platforms);
    collectible_list.swap(collectibles);

    return true;
}

}
