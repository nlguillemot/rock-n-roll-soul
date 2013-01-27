#include "player.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>

namespace heart
{

Player::Player():
Entity("rocker")
{
    init();
}

Player::~Player()
{
    cleanup();
}

void Player::init()
{
    reload_entity_data();

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

    const sf::Vector2f* aimer_scale = aimer_->maybe_point("scale");
    if (aimer_scale)
    {
        aimer_->set_scale(*aimer_scale);
    }

    aimer_->set_hidden(true);

    // set default values
    state_ = PlayerState::Idle;
    direction_ = Right;

    movement_speed_ = 100.0f;
    movement_velocity_ = sf::Vector2f(0.0f,0.0f);

    aim_angle_ = 45.0f;
    aim_movement_ = Up;
    aim_rotation_speed_ = 90.0f;
    current_aim_speed_ = 0.0f;

    const float* charge_time = animation_->maybe_constant("charge_time");
    if (charge_time)
    {
        if (std::fabs(*charge_time) < 0.001)
        {
            launch_charge_speed_ = 1000;
        }
        else
        {
            launch_charge_speed_ = 1/(*charge_time);
        }
    }
    else
    {
        launch_charge_speed_ = 1.3f;
    }
    launch_charge_ = 0.0f;

    gravity_ = sf::Vector2f(0.0f,200.0f);
    current_gravity_ = sf::Vector2f(0.0f,0.0f);

    friction_constant_ = 200.0f;

    position_ = sf::Vector2f(0.0f,0.0f);
    velocity_ = sf::Vector2f(0.0f,0.0f);
    acceleration_ = sf::Vector2f(0.0f,0.0f);

    // allow mechanism to properly switch state
    switch_to_state(PlayerState::Idle);
    switch_direction(Right);
}

void Player::cleanup()
{
    delete aimer_;
    delete aimer_data_;
}

void Player::reset_state()
{
    cleanup();
    init();
}

PlayerState Player::state() const
{
    return state_;
}

Player::Direction Player::direction() const
{
    return direction_;
}

sf::Vector2f Player::position() const
{
    return position_;
}

void Player::snap_to_position(const sf::Vector2f& pos)
{
    position_ = pos;
    animation_->set_position(position_);
}

sf::Vector2f Player::feet_relative() const
{
    return position_;
}

sf::FloatRect Player::feet_rect() const
{
    float animwidth = animation_->anim_rect().GetWidth();
    float animheight = animation_->anim_rect().GetHeight();
    return sf::FloatRect(
        position_.x - animwidth*0.15,
        position_.y - animheight*0.25,
        position_.x + animwidth*0.15,
        position_.y);
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

bool Player::falling() const
{
    return state_ == PlayerState::Falling;
}

bool Player::in_air() const
{
    return element_of(state_,states_in_the_air);
}

void Player::launch()
{
    if (state_ != PlayerState::Launching)
    {
        return;
    }

    float angle_with_direction =
        direction_ == Left ?
        180 - aim_angle_ : aim_angle_;

    sf::Vector2f launch_vector = unit_vector_from_angle(angle_with_direction);
    std::cout << "Launch angle: " << aim_angle_ << std::endl;
    launch_vector *= launch_charge_ * launch_impulse_speed_;
    launch_vector.y *= -1;
    std::cout << "Launch vector: " << launch_vector << std::endl;

    velocity_ += launch_vector;

    switch_to_state(PlayerState::Flying);
}

void Player::land_at_y(float y)
{
    if (state_ != PlayerState::Falling)
    {
        return;
    }

    position_.y = y;
    switch_to_state(PlayerState::Landing);
}

void Player::switch_to_state(PlayerState next_state)
{
    log_message("Player switching to state: " + to_string(next_state));

    animation_->play(animation_from_state(next_state));

    if (element_of(next_state,states_without_looping_animations))
    {
        animation_->set_looping(false);
    }
    else
    {
        animation_->set_looping(true);
    }

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

    if (state_ == PlayerState::Launching)
    {
        launch_charge_ = 0.0f;
    }

    if (element_of(state_,states_in_the_air))
    {
        if (!element_of(next_state,states_in_the_air))
        {
            current_gravity_ = sf::Vector2f(0.0f,0.0f);
            velocity_.y = 0.0f;
        }
    }
    else
    {
        if (element_of(next_state,states_in_the_air))
        {
            current_gravity_ = gravity_;
            velocity_ += movement_velocity_;
        }
    }

    if (element_of(next_state, states_with_movement))
    {
        update_movement_velocity(movement_speed_);
    }
    else
    {
        update_movement_velocity(0);
    }

    state_ = next_state;
}

void Player::switch_direction(Direction next_direction)
{
    bool switched_direction = direction_ != next_direction;

    direction_ = next_direction;

    if (switched_direction && element_of(state_, states_with_direction_switching))
    {
        update_movement_velocity(std::fabs(movement_velocity_.x));
    }
}

void Player::update(sf::Uint32 dt)
{
    float dtf = dt/1000.0f;

    if (state_ == PlayerState::Launching)
    {
        launch_charge_ += launch_charge_speed_ * dtf;
        launch_charge_ = clamp(launch_charge_,0.0f,1.0f);
    }

    aimer_->hold(
        clamp(aimer_->sequence_frame("charge") +
         int(aimer_->sequence_duration("charge") * launch_charge_),
         0, aimer_->sequence_duration("charge") - 1));

    sf::Vector2f friction(0.0f,0.0f);
    if (!element_of(state_,states_in_the_air))
    {
        friction.x = -signum(velocity_.x);
        friction *= friction_constant_;
    }

    velocity_ += dtf * (acceleration_ + current_gravity_);
    
    float velocity_after_friction = velocity_.x + dtf * friction.x;
    // apply friction
    if (signum(velocity_.x) !=
        signum(velocity_after_friction))
    {
        float dv = velocity_after_friction - velocity_.x;
        float ratio = (0 - velocity_.x) / dv;

        position_.x += dtf * (velocity_.x + ratio * dv);
        velocity_.x = 0.0f;
    }
    else
    {
        velocity_.x = velocity_after_friction;
    }

    position_ += dtf * (velocity_ + movement_velocity_);
    rotate_aim(dtf * current_aim_speed_);

    if (state_ == PlayerState::Flying)
    {
        if (velocity_.y >= 0.0f)
        {
            switch_to_state(PlayerState::Falling);
        }
    }

    if (state_ == PlayerState::Landing)
    {
        if (!animation_->playing())
        {
            switch_to_state(PlayerState::Idle);
        }
    }

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
