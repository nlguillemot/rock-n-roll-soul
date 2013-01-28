#pragma once

#include "effect.hpp"
#include "tween.hpp"

namespace heart
{

class Fader : public Effect
{
public:
    Fader(const Animation& anim, bool fadeout, const sf::Vector2f& position, float time, TweenFunction tween);
    
    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
    bool done() const;
private:
    bool fadeout_;
    Tweener tweener_;
};

}
