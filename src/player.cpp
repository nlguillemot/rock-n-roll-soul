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

    // set default values
    state_ = Idle;
    direction_ = Right;
    movement_speed_ = 100.0f;

    // allow mechanism to properly switch state
    switch_to_state(Idle);
    switch_direction(Right);
}

Player::~Player()
{
    delete anim_data_;
    delete animation_;
}

static std::string to_string(Player::State state)
{
    switch (state)
    {
        case Player::Idle: return "Idle";
        case Player::Moving: return "Moving";
        case Player::Jumping: return "Jumping";
        case Player::Falling: return "Falling";
        default: return "Unknown";
    }
}

Player::State Player::state() const
{
    return state_;
}

Player::Direction Player::direction() const
{
    return direction_;
}

void Player::switch_to_state(State next_state)
{
    log_message("Player switching to state: " + to_string(next_state));

    if (next_state == Idle)
    {
        animation_->play("idle");
        update_movement_velocity(0);
    }
    else if (next_state == Moving)
    {
        animation_->play("move");
        update_movement_velocity(movement_speed_);
    }
    else if (next_state == Jumping)
    {
        animation_->play("jump");
    }
    else if (next_state == Falling)
    {
        animation_->play("fall");
    }
    else
    {
    }

    state_ = next_state;
}

void Player::switch_direction(Direction next_direction)
{
    bool switched_direction = direction_ != next_direction;

    animation_->fliph(next_direction == Left);

    direction_ = next_direction;

    if (switched_direction && state_ == Moving)
    {
        update_movement_velocity(movement_speed_);
    }
}

void Player::update(sf::Uint32 dt)
{
    if (state_ == Idle)
    {
    }
    else if (state_ == Moving)
    {
    }
    else if (state_ == Jumping)
    {
    }
    else if (state_ == Falling)
    {
    }
    else
    {
    }

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
    animation_->draw(target);
}

}
