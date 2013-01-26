#include "heart.hpp"

namespace heart
{

Heart::Heart()
{
    anim_data_ = new AnimData("assets/heart");
    animation_ = new Animation(*anim_data_);
    state_ = Idle;
}

Heart::~Heart()
{
    delete anim_data_;
    delete animation_;
}

void Heart::update(sf::Uint32 dt)
{
    if (state_ == Idle)
    {
	
    }
    else
    {
    }

    velocity_ = (dt/1000.0f) * acceleration_;
    position_ = (dt/1000.0f) * velocity_;
}

void Heart::draw(sf::RenderTarget& target)
{
    animation_->set_position(position_);
    animation_->draw(target);
}

}
