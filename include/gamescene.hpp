#pragma once
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "animdata.hpp"
#include "animation.hpp"

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
    AnimData* bird_data_;
    Animation* bird_;
};

}
