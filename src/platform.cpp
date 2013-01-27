#include "platform.hpp"

#include <iostream>

namespace heart
{

Platform::Platform(const std::string& style)
{
    anim_data_ = new AnimData("assets/" + style);
    animation_ = new Animation(*anim_data_);

    const sf::Vector2f* origin = animation_->maybe_point("origin");

    if (origin)
    {
        animation_->set_origin(*origin);
    }

    const sf::Vector2f* scaling = animation_->maybe_point("scale");
    if (scaling)
    {
        animation_->set_scale(*scaling);
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
    animation_->set_position(position_);
}

sf::FloatRect Platform::collision_area() const
{
    sf::FloatRect rect(animation_->anim_rect_relative());
    return rect;
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
