#include "explosion.hpp"
#include "util.hpp"

namespace heart
{

Explosion::Explosion(const Animation& anim, const sf::Vector2f& center, float speed, float range, TweenFunction tween):
Effect(anim),
tweener_(tween,range/speed)
{
    center_ = center;
    range_ = range;
}

void Explosion::update(sf::Uint32 dt)
{
    tweener_.update(dt);
}

void Explosion::draw(sf::RenderTarget& target)
{
    float angles[] = { 0, 45, 90, 135, 180, 225, 270, 315 };
    int num_angles = sizeof(angles)/sizeof(*angles);

    float ratio = tweener_.out_value();
    ratio = clamp(ratio, 0.0f, 1.0f);

    for (int i = 0; i < num_angles; i++)
    {
        sf::Vector2f v = unit_vector_from_angle(angles[i]);
        v *= range_ * ratio;

        float alpha = 255 * (1.0f - ratio);

        animation().set_position(center_ + v);
        animation().set_alpha(alpha);
        animation().draw(target);
    }
}

bool Explosion::done() const
{
    return tweener_.done();
}

}
