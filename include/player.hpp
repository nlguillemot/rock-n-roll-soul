#pragma once

#include <SFML/Graphics.hpp>
#include "animation.hpp"
#include "playerstate.hpp"
#include "animdata.hpp"

namespace heart
{

class Player
{
public:
    enum Direction
    {
        Left,
        Right
    };

    Player();
    ~Player();

    PlayerState state() const;
    Direction direction() const;

    void snap_to_position(const sf::Vector2f& pos);

    float aim_angle() const;
    void set_aim_angle(float angle);
    void rotate_aim(float rotation);

    void switch_to_state(PlayerState next_state);
    void switch_direction(Direction next_direction);

    void update(sf::Uint32 dt);

    void draw(sf::RenderTarget& target);
private:
    void update_movement_velocity(float speed);

    AnimData* anim_data_;
    Animation* animation_;

    AnimData* aimer_data_;
    Animation* aimer_;

    PlayerState state_;

    Direction direction_;
    
    // angle in degrees from horizontal
    float aim_angle_;

    // degrees per second
    float aim_rotation_speed_;

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
