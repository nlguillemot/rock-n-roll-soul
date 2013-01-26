#pragma once

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "player.hpp"

namespace heart
{

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();
    void handle_event(const sf::Event& e);
    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
private:
    void player_handle_keydown(sf::Key::Code code);

    Player player_;
};

}
