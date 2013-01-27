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
        Up,
        Down,
        Left,
        Right
    };

    Player();
    ~Player();

    PlayerState state() const;
    Direction direction() const;

    sf::Vector2f position() const;
    void snap_to_position(const sf::Vector2f& pos);

    sf::Vector2f feet_relative() const;

    sf::FloatRect feet_rect() const;

    const sf::Vector2f& gravity_effect() const;
    void set_gravity_effect(const sf::Vector2f& gravity);

    float aim_angle() const;
    void set_aim_movement(Direction up_or_down);
    void begin_aim_movement();
    void stop_aim_movement();

    bool falling() const;
    bool in_air() const;

    void launch();
    void land_at_y(float y);

    void switch_to_state(PlayerState next_state);
    void switch_direction(Direction next_direction);

    void update(sf::Uint32 dt);

    void draw(sf::RenderTarget& target);
private:
    void set_aim_angle(float angle);
    void rotate_aim(float rotation);
    void update_movement_velocity(float speed);

    AnimData* anim_data_;
    Animation* animation_;

    AnimData* aimer_data_;
    Animation* aimer_;

    PlayerState state_;

    Direction direction_;

    // angle in degrees from horizontal
    float aim_angle_;
    Direction aim_movement_;
    // degrees per second
    float aim_rotation_speed_; // constant ish
    float current_aim_speed_; // actually used

    // percent per second (0 to 1)
    float launch_charge_speed_;
    float launch_impulse_speed_;
    float launch_charge_;

    // pixels per second
    float movement_speed_;
    // component of velocity from player input
    sf::Vector2f movement_velocity_;

    // pixels per second^2
    sf::Vector2f gravity_; // constant-ish
    sf::Vector2f current_gravity_; // actually used

    // pixels per second^2
    float friction_constant_;

    // components of physics from outside effects
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
};

}
