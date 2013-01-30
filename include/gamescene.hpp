#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "explosion.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "gamemap.hpp"
#include "entity.hpp"

#include <list>
#include <random>

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
    void update(float dt);
    void draw(sf::RenderTarget& target);
    void exit();
private:
    void init_world();
    void cleanup_world();
    void player_handle_keydown(sf::Key::Code code);
    void player_handle_keyup(sf::Key::Code code);

    void update_player(float dt);

    void update_camera(float dt);
    void move_camera_to(const sf::Vector2f& p);

    void update_effects(float dt);

    void explode(Entity* e, bool and_disappear);

    GameMap map_;

    AnimData* background_data_;
    Animation* background_;

    PlayerKeys player_keys_;
    Player player_;

    std::vector<Entity*> platforms_;
    std::vector<Entity*> goalflags_;
    std::vector<Entity*> collectibles_;
    std::vector<Entity*> decorations_;

    std::list<Effect*> effects_;

    std::string level_name_;

    sf::Music bgm_;

    sf::SoundBuffer collectsndbuf_;
    sf::Sound collectsnd_;

    sf::Vector2f camera_zoom_;
    sf::Vector2f camera_zoom_target_;
    float camera_zoom_lerp_ratio_;

    sf::Vector2f camera_position_;
    sf::Vector2f camera_target_;
    float camera_pan_lerp_ratio_;

    std::mt19937 random_music_note_;
    float music_note_timer_;
    std::vector<Entity*> music_notes_;
};

}
