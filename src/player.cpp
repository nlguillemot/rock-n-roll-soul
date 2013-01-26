#include "player.hpp"

namespace heart
{

Player::Player()
{
    anim_data_ = new AnimData("assets/bird");
    animation_ = new Animation(*anim_data_);
    state_ = Idle;
}

Player::~Player()
{
    delete anim_data_;
    delete animation_;
}

void Player::update(sf::Uint32 dt)
{
    if (state_ == Idle)
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

    velocity_ = (dt/1000.0f) * acceleration_;
    position_ = (dt/1000.0f) * velocity_;
}

void Player::draw(sf::RenderTarget& target)
{
    animation_->set_position(position_);
    animation_->draw(target);
}

}
