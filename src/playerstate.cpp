#include "playerstate.hpp"

namespace heart
{

const std::vector<PlayerState> states_with_aimer_visible =
{
    PlayerState::Idle,
    PlayerState::Moving,
    PlayerState::Launching,
    PlayerState::Landing,
};

const std::vector<PlayerState> states_allowing_launching =
{
    PlayerState::Idle,
    PlayerState::Moving,
    PlayerState::Landing
};

const std::vector<PlayerState> states_allowing_aiming =
{
    PlayerState::Idle,
    PlayerState::Moving,
    PlayerState::Launching,
    PlayerState::Landing
};

const std::vector<PlayerState> states_with_movement =
{
    PlayerState::Moving,
};

const std::vector<PlayerState> states_with_direction_switching =
{
    PlayerState::Idle,
    PlayerState::Moving,
    PlayerState::Launching,
    PlayerState::Flying,
    PlayerState::Falling,
    PlayerState::Landing
};

const std::vector<PlayerState> states_in_the_air =
{
    PlayerState::Flying,
    PlayerState::Falling,
    PlayerState::Winning
};

const std::vector<PlayerState> states_without_looping_animations =
{
    PlayerState::Landing
};

std::string to_string(PlayerState state)
{
    switch (state)
    {
        case PlayerState::Idle: return "Idle";
        case PlayerState::Moving: return "Moving";
        case PlayerState::Launching: return "Launching";
        case PlayerState::Flying: return "Flying";
        case PlayerState::Falling: return "Falling";
        case PlayerState::Landing: return "Landing";
        case PlayerState::Winning: return "Winning";
        default: return "Unknown";
    }
}

std::string animation_from_state(PlayerState state)
{
    switch (state)
    {
        case PlayerState::Idle: return "idle";
        case PlayerState::Moving: return "move";
        case PlayerState::Launching: return "launching";
        case PlayerState::Flying: return "fly";
        case PlayerState::Falling: return "fall";
        case PlayerState::Landing: return "land";
        case PlayerState::Winning: return "winning";
        default: return "";
    }
}

}
