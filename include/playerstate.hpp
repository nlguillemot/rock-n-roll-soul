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
    Landing
};

extern const std::vector<PlayerState> states_with_aimer;
extern const std::vector<PlayerState> states_where_you_can_start_moving;
extern const std::vector<PlayerState> states_with_movement;
extern const std::vector<PlayerState> states_with_direction_switching;

std::string to_string(PlayerState state);
std::string animation_from_state(PlayerState state);

}
