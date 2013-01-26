#include "platform.hpp"

#include <iostream>

namespace heart
{

Platform::Platform(const std::string& style)
{
    std::cout << "Platform(assets/" << style << ")" << std::endl;
    anim_data_ = new AnimData("assets/" + style);
    animation_ = new Animation(*anim_data_);

    const sf::Vector2f* origin = animation_->maybe_point("origin");

    if (origin)
    {
        animation_->set_origin(*origin);
    }
}

Platform::~Platform()
{
    delete animation_;
    delete anim_data_;
}

void Platform::snap_to_position(const sf::Vector2f& position)
{
    position_ = position;
}

void Platform::update(sf::Uint32 dt)
{
    animation_->update(dt);
}

void Platform::draw(sf::RenderTarget& target)
{
    animation_->set_position(position_);
    animation_->draw(target);
}

}
