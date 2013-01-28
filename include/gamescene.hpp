#pragma once

#include <SFML/Graphics.hpp>
#include "explosion.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "gamemap.hpp"
#include "entity.hpp"

#include <list>

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
    GameScene(const std::string& level);
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

    void update_player(sf::Uint32 dt);
    void update_camera();
    void update_explosions(sf::Uint32 dt);

    void explode(Entity* e);

    GameMap map_;

    AnimData* background_data_;
    Animation* background_;

    PlayerKeys player_keys_;
    Player player_;

    std::vector<Entity*> platforms_;
    std::vector<Entity*> goalflags_;
    std::vector<Entity*> collectibles_;
    std::vector<Entity*> decorations_;

    std::list<Explosion> explosions_;

    std::string level_name_;
};

}
