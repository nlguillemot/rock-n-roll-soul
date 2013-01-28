#pragma once

#include "animation.hpp"
#include "sequencer.hpp"

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

    virtual sf::FloatRect bounding_box() const;
    virtual sf::FloatRect collision_area() const;

    Animation* animation() const;

    virtual void update(sf::Uint32 dt);
    virtual void draw(sf::RenderTarget& target);

    Sequencer& sequencer();
protected:
    Animation* animation_;
    AnimData* anim_data_;

    sf::Vector2f position_;

    Sequencer sequencer_;
};

}
