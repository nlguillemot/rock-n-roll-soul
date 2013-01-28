#include "explosion.hpp"
#include "util.hpp"

namespace heart
{

Explosion::Explosion(Animation* anim, const sf::Vector2f& center, float speed, float range)
{
    anim_ = anim;
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

        sf::Vector2f oldpos = anim_->position();
        float oldalpha = anim_->alpha();
        bool oldhidden = anim_->hidden();

        anim_->set_position(center_ + v);
        anim_->set_alpha(alpha);
        anim_->set_hidden(false);
        anim_->draw(target);

        anim_->set_position(oldpos);
        anim_->set_alpha(oldalpha);
        anim_->set_hidden(oldhidden);
    }
}

bool Explosion::done() const
{
    return dist_ >= range_;
}

}
