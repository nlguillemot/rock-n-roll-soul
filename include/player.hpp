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
        Moving,
        Jumping,
        Falling
    };

    enum Direction
    {
        Left,
        Right
    };

    Player();
    ~Player();

    State state() const;
    Direction direction() const;

    void switch_to_state(State next_state);
    void switch_direction(Direction next_direction);

    void update(sf::Uint32 dt);

    void draw(sf::RenderTarget& target);
private:
    void update_movement_velocity(float speed);

    Animation* animation_;
    AnimData* anim_data_;

    State state_;

    Direction direction_;
    
    // pixels per second
    float movement_speed_;
    // component of velocity from player input
    sf::Vector2f movement_velocity_;

    // components of physics from outside effects
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
};

}
