#include "effect.hpp"

namespace heart
{

Effect::Effect(const Animation& anim):
anim_(anim)
{
}

Effect::~Effect()
{
}

const Animation& Effect::animation() const
{
    return anim_;
}

Animation& Effect::animation()
{
    return anim_;
}

}
