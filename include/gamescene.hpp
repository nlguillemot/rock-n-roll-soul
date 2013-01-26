#pragma once

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "player.hpp"

namespace heart
{

struct KeyState
{
    KeyState()
    {
    }

    KeyState(sf::Key::Code key):
    key(key),
    held(false)
    {
    }

    sf::Key::Code key;
    bool held;
};

struct PlayerKeys
{
    KeyState left;
    KeyState right;
    KeyState up;
    KeyState down;
    KeyState action;
};

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
    void player_handle_keyup(sf::Key::Code code);

    PlayerKeys player_keys_;
    Player player_;
};

}
