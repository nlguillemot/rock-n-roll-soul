#pragma once

#include <SFML/Graphics.hpp>
#include "animation.hpp"
#include "animdata.hpp"

namespace heart
{

class Player
{
public:
    enum State
    {
        Idle,
        Jumping,
        Falling
    };

    Player();
    ~Player();

    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
private:
    Animation* animation_;
    AnimData* anim_data_;

    State state_;
    
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
};

}
