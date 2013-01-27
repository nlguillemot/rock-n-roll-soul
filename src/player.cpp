#include "player.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>

namespace heart
{

Player::Player()
{
    anim_data_ = new AnimData("assets/rocker");
    animation_ = new Animation(*anim_data_);

    animation_->set_origin(sf::Vector2f(0.5f,1.0f));

    const sf::Vector2f* rocker_scale = animation_->maybe_point("scale");
    if (rocker_scale)
    {
        std::cout << "Read scale: "
            << rocker_scale->x
            << "," << rocker_scale->y << std::endl;
        animation_->set_scale(*rocker_scale);
    }

    const float* launch_speed = animation_->maybe_constant("launch_speed");
    if (launch_speed)
    {
        launch_impulse_speed_ = *launch_speed;
    }
    else
    {
        launch_impulse_speed_ = 150.0f;
    }

    aimer_data_ = new AnimData("assets/aimer");
    aimer_ = new Animation(*aimer_data_);

    aimer_->set_alpha(128);

    sf::Vector2f aimer_origin = aimer_->point("origin");
    aimer_->set_origin(aimer_origin);

    aimer_->set_hidden(true);

    // set default values
    state_ = PlayerState::Idle;
    direction_ = Right;

    movement_speed_ = 100.0f;

    aim_angle_ = 45.0f;
    aim_movement_ = Up;
    aim_rotation_speed_ = 90.0f;
    current_aim_speed_ = 0.0f;

    launch_charge_speed_ = 1.0f;
    launch_charge_ = 0.0f;

    gravity_ = sf::Vector2f(0.0f,200.0f);
    current_gravity_ = sf::Vector2f(0.0f,0.0f);

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

const sf::Vector2f& Player::gravity_effect() const
{
    return gravity_;
}

void Player::set_gravity_effect(const sf::Vector2f& gravity)
{
    gravity_ = gravity;
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

void Player::set_aim_movement(Direction dir)
{
    aim_movement_ = dir;
}

void Player::begin_aim_movement()
{
    current_aim_speed_ = aim_rotation_speed_;
    if (aim_movement_ == Down)
    {
        current_aim_speed_ *= -1;
    }
}

void Player::stop_aim_movement()
{
    current_aim_speed_ = 0.0f;
}

void Player::launch()
{
    if (state_ != PlayerState::Launching)
    {
        return;
    }

    sf::Vector2f launch_vector = unit_vector_from_angle(aim_angle_);
    launch_vector *= launch_charge_ * launch_impulse_speed_;
    launch_vector.y *= -1;

    velocity_ += launch_vector;

    switch_to_state(PlayerState::Flying);
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

    if (element_of(next_state, states_with_aimer_visible))
    {
        aimer_->set_hidden(false);
    }
    else
    {
        aimer_->set_hidden(true);
    }

    if (next_state == PlayerState::Launching)
    {
        launch_charge_ = 0.0f;
    }

    if (element_of(state_,states_in_the_air))
    {
        if (!element_of(next_state,states_in_the_air))
        {
            current_gravity_ = sf::Vector2f(0.0f,0.0f);
        }
    }
    else
    {
        if (element_of(next_state,states_in_the_air))
        {
            current_gravity_ = gravity_;
        }
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
    float dtf = dt/1000.0f;

    if (state_ == PlayerState::Launching)
    {
        launch_charge_ += launch_charge_speed_ * dtf;
        clamp(launch_charge_,0.0f,1.0f);
    }

    velocity_ += dtf * (acceleration_ + current_gravity_);
    position_ += dtf * (velocity_ + movement_velocity_);
    rotate_aim(dtf * current_aim_speed_);

    animation_->update(dt);
    aimer_->update(dt);
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
    aimer_->set_position(animation_->center_relative());

    bool facing_left = direction_ == Left;
    animation_->fliph(facing_left);

    float actual_rotation = aim_angle_;
    if (facing_left)
    {
        actual_rotation *= -1;
    }

    aimer_->fliph(facing_left);
    aimer_->set_rotation(actual_rotation);

    animation_->draw(target);
    aimer_->draw(target);
}

}
