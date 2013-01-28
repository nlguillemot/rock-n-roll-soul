#pragma once

#include "animation.hpp"

namespace heart
{

class Explosion
{
public:
    Explosion(Animation* anim, const sf::Vector2f& center, float speed, float range);

    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
    bool done() const;
private:
    float dist_;
    sf::Vector2f center_;
    float speed_;
    float range_;
    Animation* anim_;
};

}
