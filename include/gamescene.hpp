#pragma once

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "player.hpp"
#include "gamemap.hpp"
#include "entity.hpp"

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
    void init();
    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
private:
    void init_world();
    void cleanup_world();
    void player_handle_keydown(sf::Key::Code code);
    void player_handle_keyup(sf::Key::Code code);

    GameMap map_;

    AnimData* background_data_;
    Animation* background_;

    PlayerKeys player_keys_;
    Player player_;

    std::vector<Entity*> platforms_;
    std::vector<Entity*> goalflags_;
};

}
