#include "mainapp.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include "gamescene.hpp"

int main()
{
    std::string gametitle;
    sf::Vector2i screensize;

    std::ifstream ifs("assets/config.dat");

    if (!ifs)
    {
        std::cout << "Could not find config.dat" << std::endl;
        return -1;
    }
    
    for (;;)
    {
        std::string current_line;
        std::getline(ifs,current_line);

        if (!current_line.empty())
        {
            std::istringstream line_stream(current_line);
            std::string property_name;

            line_stream >> property_name;

            if (property_name == "gametitle")
            {
                line_stream >> gametitle;
            }
            else if (property_name == "screensize")
            {
                line_stream >> screensize.x;
                line_stream >> screensize.y;
            }
        }
        if (ifs.eof())
        {
            break;
        }
        else if (ifs.bad())
        {
            assert(false);
            break;
        }
    }

    ifs.close();

    heart::MainApp app(sf::VideoMode(screensize.x,screensize.y), gametitle, new heart::GameScene());
    app.exec();
}
