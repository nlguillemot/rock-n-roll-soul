#pragma once

#include "effect.hpp"
#include "tween.hpp"

namespace heart
{

class Explosion : public Effect
{
public:
    Explosion(const Animation& anim, const sf::Vector2f& center, float speed, float range, TweenFunction tween);

    void update(float dt);
    void draw(sf::RenderTarget& target);
    bool done() const;
private:
    sf::Vector2f center_;
    float range_;
    Tweener tweener_;
};

}
