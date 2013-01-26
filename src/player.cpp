#include "player.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>

namespace heart
{

Player::Player()
{
    anim_data_ = new AnimData("assets/bird");
    animation_ = new Animation(*anim_data_);

    animation_->set_origin(sf::Vector2f(0.5f,1.0f));

    aimer_data_ = new AnimData("assets/aimer");
    aimer_ = new Animation(*aimer_data_);
    aimer_->set_alpha(128);
    sf::Vector2f aimer_origin = aimer_->point("origin");
    aimer_->set_origin(aimer_origin);

    aimer_->set_hidden(true);

    // set default values
    state_ = PlayerState::Idle;
    direction_ = Right;
    aim_angle_ = 45.0f;
    movement_speed_ = 100.0f;
    aim_rotation_speed_ = 90.0f;

    // allow mechanism to properly switch state
    switch_to_state(PlayerState::Idle);
    switch_direction(Right);
}

Player::~Player()
{
    delete aimer_;
    delete aimer_data_;

    delete animation_;
    delete anim_data_;
}

PlayerState Player::state() const
{
    return state_;
}

Player::Direction Player::direction() const
{
    return direction_;
}

void Player::snap_to_position(const sf::Vector2f& pos)
{
    position_ = pos;
}

float Player::aim_angle() const
{
    return aim_angle_;
}

void Player::set_aim_angle(float angle)
{
    aim_angle_ = clamp(angle,0.0f,90.0f);
}

void Player::rotate_aim(float rotation)
{
    set_aim_angle(aim_angle() + rotation);
}

void Player::switch_to_state(PlayerState next_state)
{
    log_message("Player switching to state: " + to_string(next_state));

    if (element_of(next_state, states_with_movement))
    {
        update_movement_velocity(movement_speed_);
    }
    else
    {
        update_movement_velocity(0);
    }

    animation_->play(animation_from_state(next_state));

    if (element_of(next_state, states_with_aimer))
    {
        aimer_->set_hidden(false);
    }
    else
    {
        aimer_->set_hidden(true);
    }

    state_ = next_state;
}

void Player::switch_direction(Direction next_direction)
{
    bool switched_direction = direction_ != next_direction;

    direction_ = next_direction;

    if (switched_direction && element_of(state_, states_with_movement))
    {
        update_movement_velocity(movement_speed_);
    }
}

void Player::update(sf::Uint32 dt)
{
    velocity_ += (dt/1000.0f) * acceleration_;
    position_ += (dt/1000.0f) * (velocity_ + movement_velocity_);
}

void Player::update_movement_velocity(float speed)
{
    movement_velocity_ = sf::Vector2f(speed,0.0f);
    if (direction_ == Left)
    {
        movement_velocity_.x *= -1;
    }
}

void Player::draw(sf::RenderTarget& target)
{
    animation_->set_position(position_);
    aimer_->set_position(animation_->position());

    bool facing_left = direction_ == Left;
    animation_->fliph(facing_left);

    float actual_rotation = aim_angle_;
    if (facing_left)
    {
        actual_rotation *= -1;
    }

    aimer_->fliph(facing_left);
    aimer_->set_rotation(actual_rotation);

    aimer_->draw(target);
    animation_->draw(target);
}

}
