#include "player.hpp"

namespace heart
{

Player::Player()
{
    anim_data_ = new AnimData("assets/bird");
    animation_ = new Animation(*anim_data_);
}

Player::~Player()
{
    delete anim_data_;
    delete animation_;
}

void Player::draw(sf::RenderTarget& target)
{
    animation_->draw(target);
}

}
