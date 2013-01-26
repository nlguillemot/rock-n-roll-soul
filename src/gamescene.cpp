#include "gamescene.hpp"

namespace heart
{

GameScene::GameScene()
{
    bird_data_ = new AnimData("assets/bird");
    bird_ = new Animation(*bird_data_);
}

GameScene::~GameScene()
{
    delete bird_data_;
    delete bird_;
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

    bird_->draw(target);
}

}
