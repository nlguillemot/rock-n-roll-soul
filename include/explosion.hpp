#pragma once

#include "effect.hpp"

namespace heart
{

class Explosion : public Effect
{
public:
    Explosion(const Animation& anim, const sf::Vector2f& center, float speed, float range);

    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
    bool done() const;
private:
    float dist_;
    sf::Vector2f center_;
    float speed_;
    float range_;
};

}
