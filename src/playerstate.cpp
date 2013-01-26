#include "playerstate.hpp"

namespace heart
{

const std::vector<PlayerState> states_with_aimer =
{
    PlayerState::Idle,
    PlayerState::Moving
};

const std::vector<PlayerState> states_where_you_can_start_moving = 
{
    PlayerState::Idle
};

const std::vector<PlayerState> states_with_movement =
{
    PlayerState::Moving,
    PlayerState::Flying,
    PlayerState::Falling
};

const std::vector<PlayerState> states_with_direction_switching =
{
    PlayerState::Idle,
    PlayerState::Moving
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
        default: return "";
    }
}

}
