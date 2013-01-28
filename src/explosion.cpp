#include "explosion.hpp"
#include "util.hpp"

namespace heart
{

Explosion::Explosion(const Animation& anim, const sf::Vector2f& center, float speed, float range):
Effect(anim)
{
    dist_ = 0;
    center_ = center;
    speed_ = speed;
    range_ = range;
}

void Explosion::update(sf::Uint32 dt)
{
    dist_ += (dt / 1000.0f) * speed_;
}

void Explosion::draw(sf::RenderTarget& target)
{
    float angles[] = { 0, 45, 90, 135, 180, 225, 270, 315 };
    int num_angles = sizeof(angles)/sizeof(*angles);

    for (int i = 0; i < num_angles; i++)
    {
        sf::Vector2f v = unit_vector_from_angle(angles[i]);
        v *= dist_;

        float ratio = dist_/range_;
        ratio = clamp(ratio, 0.0f, 1.0f);
        float alpha = 255 * (1.0f - ratio);

        animation().set_position(center_ + v);
        animation().set_alpha(alpha);
        animation().draw(target);
    }
}

bool Explosion::done() const
{
    return dist_ >= range_;
}

}
