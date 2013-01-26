#pragma once

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "player.hpp"
#include "gamemap.hpp"

namespace heart
{

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void handle_event(const sf::Event& e);
    void init();
    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
private:
    Player player_;
    GameMap map_;
};

}
