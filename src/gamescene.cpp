#include "gamescene.hpp"
#include <iostream>

namespace heart
{

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
    if (!map_.load_from_file("assets/level1.map"))
    {
        std::cout << "Failed to load map." << std::endl;
    }

    for (std::list<GameMap::Platform>::iterator it = map_.platform_list.begin();
            it != map_.platform_list.end(); ++it)
    {
        std::cout << "Got platform:"
            << " asset_name: " << it->asset_name
            << " position: { " << it->position.x << ", "
            << it->position.y << " }" << std::endl;
    }

    for (std::list<GameMap::Collectible>::iterator it = map_.collectible_list.begin();
            it != map_.collectible_list.end(); ++it)
    {
        std::cout << "Got collectible:"
            << " type: " << it->type
            << " position: { " << it->position.x << ", "
            << it->position.y << " }" << std::endl;
    }
}

template<class T>
bool element_of(const T& elm, const std::vector<T>& v)
{
    return std::find(v.begin(),v.end(),elm) != v.end();
}

void GameScene::handle_event(const sf::Event& e)
{
    const std::vector<sf::Key::Code> movement_keys = {
        sf::Key::Left,
        sf::Key::Right
    };

    if (e.Type == sf::Event::KeyPressed)
    {
        if (element_of(e.Key.Code,movement_keys))
        {
            if (player_.state() == Player::Idle)
            {
                if (e.Key.Code == sf::Key::Left)
                {
                    player_.switch_to_state(Player::Moving);
                }
                else if (e.Key.Code == sf::Key::Right)
                {
                    player_.switch_to_state(Player::Moving);
                }
            }

            if (e.Key.Code == sf::Key::Left)
            {
                player_.switch_direction(Player::FacingLeft);
            }
            else if (e.Key.Code == sf::Key::Right)
            {
                player_.switch_direction(Player::FacingRight);
            }
        }
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
