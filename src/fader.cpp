#include "fader.hpp"
#include "util.hpp"

namespace heart
{

Fader::Fader(const Animation& anim, bool fadeout, const sf::Vector2f& position, float time, TweenFunction tween):
Effect(anim),
fadeout_(fadeout),
tweener_(tween,time)
{
    animation().set_position(position);
}

void Fader::update(float dt)
{
    tweener_.update(dt);
}

void Fader::draw(sf::RenderTarget& target)
{
    float ratio = tweener_.out_value();
    ratio = clamp(ratio, 0.0f, 1.0f);

    float alpha;
    if (fadeout_)
    {
        alpha = 255 * (1.0f - ratio);
    }
    else
    {
        alpha = 255 * ratio;
    }

    animation().set_alpha(alpha);
    animation().draw(target);
}

bool Fader::done() const
{
    return tweener_.done();
}

}
