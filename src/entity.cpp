#include "entity.hpp"

namespace heart
{

Entity::Entity(const std::string& style)
{
    anim_data_ = new AnimData("assets/" + style);
    animation_ = new Animation(*anim_data_);
    reload_entity_data();
}

Entity::~Entity()
{
    delete animation_;
    delete anim_data_;
}

void Entity::reload_entity_data()
{
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

sf::Vector2f Entity::position() const
{
    return position_;
}

void Entity::snap_to_position(const sf::Vector2f& position)
{
    position_ = position;
    animation_->set_position(position_);
}

sf::FloatRect Entity::collision_area() const
{
    sf::FloatRect rect(animation_->anim_rect_relative());
    return rect;
}

void Entity::update(sf::Uint32 dt)
{
    animation_->update(dt);
}

void Entity::draw(sf::RenderTarget& target)
{
    animation_->set_position(position_);
    animation_->draw(target);
}

}
