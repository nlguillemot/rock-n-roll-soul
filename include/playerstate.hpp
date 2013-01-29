#pragma once

#include <vector>
#include <string>

namespace heart
{

enum class PlayerState
{
    Idle,
    Moving,
    Launching,
    Flying,
    Falling,
    Landing,
    Winning
};

class PlayerStateMachine
{
public:
    bool state_with_aimer_visible(PlayerState state) const;
    bool state_allowing_aiming(PlayerState state) const;
    bool state_allowing_launching(PlayerState state) const;
    bool state_with_movement(PlayerState state) const;
    bool state_with_direction_switching(PlayerState state) const;
    bool state_in_the_air(PlayerState state) const;
    bool state_without_looping_animations(PlayerState state) const;
    bool state_with_music_notes(PlayerState state) const;
};

std::string to_string(PlayerState state);
std::string animation_from_state(PlayerState state);

}
