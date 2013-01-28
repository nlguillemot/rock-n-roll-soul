#pragma once

#include <functional>
#include <SFML/System.hpp>

namespace heart
{

typedef std::function<float (float)> TweenFunction;

class Tweener
{
public:
    Tweener(TweenFunction fn, float time_to_completion);

    void update(sf::Uint32 dt);

    float in_value() const;
    float out_value() const;
    bool done() const;
private:
    TweenFunction fn_;
    float time_to_completion_;
    float current_time_;
};

float tween_linear(float x);
float tween_sqrt(float x);
float tween_squared(float x);

}
