#include "playerstate.hpp"

namespace heart
{

bool PlayerStateMachine::state_with_aimer_visible(PlayerState state) const
{
    return
    state == PlayerState::Idle ||
    state == PlayerState::Moving ||
    state == PlayerState::Launching ||
    state == PlayerState::Landing;
}

bool PlayerStateMachine::state_allowing_aiming(PlayerState state) const
{
    return
    state == PlayerState::Idle ||
    state == PlayerState::Moving ||
    state == PlayerState::Launching ||
    state == PlayerState::Landing;
}

bool PlayerStateMachine::state_allowing_launching(PlayerState state) const
{
    return
    state == PlayerState::Idle ||
    state == PlayerState::Moving ||
    state == PlayerState::Landing;
}

bool PlayerStateMachine::state_with_movement(PlayerState state) const
{
    return
    state == PlayerState::Moving;
}

bool PlayerStateMachine::state_with_direction_switching(PlayerState state) const
{
    return
    state == PlayerState::Idle ||
    state == PlayerState::Moving ||
    state == PlayerState::Launching ||
    state == PlayerState::Flying ||
    state == PlayerState::Falling ||
    state == PlayerState::Landing;
}

bool PlayerStateMachine::state_in_the_air(PlayerState state) const
{
    return
    state == PlayerState::Flying ||
    state == PlayerState::Falling ||
    state == PlayerState::Winning;
}

bool PlayerStateMachine::state_without_looping_animations(PlayerState state) const
{
    return
    state == PlayerState::Landing;
}

bool PlayerStateMachine::state_with_music_notes(PlayerState state) const
{
    return
    state == PlayerState::Flying ||
    state == PlayerState::Falling;
}

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
