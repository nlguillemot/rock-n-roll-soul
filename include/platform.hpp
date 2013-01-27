#pragma once

#include "animation.hpp"

namespace heart
{

class Platform
{
public:
    Platform(const std::string& style);
    ~Platform();

    sf::Vector2f position() const;
    void snap_to_position(const sf::Vector2f& position);

    sf::FloatRect collision_area() const;

    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
private:
    Animation* animation_;
    AnimData* anim_data_;

    sf::Vector2f position_;
};

}
