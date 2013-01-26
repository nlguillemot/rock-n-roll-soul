#pragma once
#include <SFML/Graphics.hpp>
#include "animation.hpp"
#include "animdata.hpp"

namespace heart
{

class Player
{
public:
    Player();
    ~Player();

    void draw(sf::RenderTarget& target);
private:
    Animation* animation_;
    AnimData* anim_data_;
};

}
