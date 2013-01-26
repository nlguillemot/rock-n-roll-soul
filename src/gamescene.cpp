#include "gamescene.hpp"

namespace heart
{

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::handle_event(const sf::Event& e)
{
    // TODO: Handle events
}

void GameScene::update(sf::Uint32 dt)
{
    // TODO: Update stuff
}

void GameScene::draw(sf::RenderTarget& target)
{
    target.Clear(sf::Color::White);

    player_.draw(target);
}

}
