#include "entity.hpp"

namespace heart
{

Entity::Entity(const std::string& style)
{
    anim_data_ = new AnimData("assets/" + style);
    animation_ = new Animation(*anim_data_);

    reload_entity_data();

    if (animation_->has_sequence("idle"))
    {
        animation_->play("idle");
    }
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

void Entity::move(const sf::Vector2f& v)
{
    snap_to_position(position() + v);
}

sf::FloatRect Entity::bounding_box() const
{
    return animation_->anim_rect_relative();
}

sf::FloatRect Entity::collision_area() const
{
    return animation_->anim_rect_relative();
}

const Animation& Entity::animation() const
{
    return *animation_;
}

Animation& Entity::animation()
{
    return *animation_;
}

void Entity::update(float dt)
{
    animation_->update(dt);
}

void Entity::draw(sf::RenderTarget& target)
{
    animation_->set_position(position_);
    animation_->draw(target);
}

}
