#include "gamescene.hpp"

#include <iostream>

namespace heart
{

GameScene::GameScene()
{
    player_keys_.left = KeyState(sf::Key::Left);
    player_keys_.right = KeyState(sf::Key::Right);
    player_keys_.up = KeyState(sf::Key::Up);
    player_keys_.down = KeyState(sf::Key::Down);
    player_keys_.action = KeyState(sf::Key::Space);
}

GameScene::~GameScene()
{
}

void GameScene::handle_event(const sf::Event& e)
{
    if (e.Type == sf::Event::KeyPressed)
    {
        player_handle_keydown(e.Key.Code);
    }
    else if (e.Type == sf::Event::KeyReleased)
    {
        player_handle_keyup(e.Key.Code);
    }
}

void GameScene::player_handle_keydown(sf::Key::Code code)
{
    if (player_.state() == Player::Idle)
    {
        if (code == player_keys_.left.key)
        {
            player_.switch_to_state(Player::Moving);
            player_.switch_direction(Player::Left);
        }
        else if (code == player_keys_.right.key)
        {
            player_.switch_to_state(Player::Moving);
            player_.switch_direction(Player::Right);
        }
    }
    else if (player_.state() == Player::Moving)
    {
        if (code == player_keys_.left.key)
        {
            player_.switch_direction(Player::Left);
        }
        else if (code == player_keys_.right.key)
        {
            player_.switch_direction(Player::Right);
        }
    }

    if (code == player_keys_.left.key)
    {
        player_keys_.left.held = true;
    }
    else if (code == player_keys_.right.key)
    {
        player_keys_.right.held = true;
    }
    else if (code == player_keys_.up.key)
    {
        player_keys_.up.held = true;
    }
    else if (code == player_keys_.down.key)
    {
        player_keys_.down.held = true;
    }
    else if (code == player_keys_.action.key)
    {
        player_keys_.action.held = true;
    }
}

void GameScene::player_handle_keyup(sf::Key::Code code)
{
    if (player_.state() == Player::Moving)
    {
        if (code == player_keys_.left.key &&
            player_.direction() == Player::Left)
        {
            if (player_keys_.right.held)
            {
                player_.switch_direction(Player::Right);
            }
            else
            {
                player_.switch_to_state(Player::Idle);
            }
        }
        else if (code == player_keys_.right.key &&
                player_.direction() == Player::Right)
        {
            if (player_keys_.left.held)
            {
                player_.switch_direction(Player::Left);
            }
            else
            {
                player_.switch_to_state(Player::Idle);
            }
        }
    }

    if (code == player_keys_.left.key)
    {
        player_keys_.left.held = false;
    }
    else if (code == player_keys_.right.key)
    {
        player_keys_.right.held = false;
    }
    else if (code == player_keys_.up.key)
    {
        player_keys_.up.held = false;
    }
    else if (code == player_keys_.down.key)
    {
        player_keys_.down.held = false;
    }
    else if (code == player_keys_.action.key)
    {
        player_keys_.action.held = false;
    }
}

void GameScene::update(sf::Uint32 dt)
{
    player_.update(dt);
}

void GameScene::draw(sf::RenderTarget& target)
{
    target.Clear(sf::Color::White);

    player_.draw(target);
}

}
