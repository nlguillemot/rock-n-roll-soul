#pragma once

#include "animation.hpp"

namespace heart
{

class Entity
{
public:
    Entity(const std::string& style);
    virtual ~Entity();

    void reload_entity_data();

    virtual sf::Vector2f position() const;
    virtual void snap_to_position(const sf::Vector2f& position);

    virtual sf::FloatRect collision_area() const;

    virtual void update(sf::Uint32 dt);
    virtual void draw(sf::RenderTarget& target);
protected:
    Animation* animation_;
    AnimData* anim_data_;

    sf::Vector2f position_;
};

}
