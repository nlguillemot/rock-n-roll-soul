#pragma once

#include "animation.hpp"

namespace heart
{

class Effect
{
public:
    Effect(const Animation& anim);
    virtual ~Effect();

    virtual void update(sf::Uint32 dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual bool done() const = 0;
    const Animation& animation() const;
    Animation& animation();
private:
    Animation anim_;
};

}
